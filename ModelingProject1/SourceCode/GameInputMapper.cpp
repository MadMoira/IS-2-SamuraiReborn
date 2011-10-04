
#include <fstream>
#include "GameInputMapper.h"

#include "File.h"
#include "GameInputContext.h"


void InputMapping::MappedInput::eatAction(InputMapping::Action action)
{
  actions.erase(action); 
}

void InputMapping::MappedInput::eatState(InputMapping::State state)
{
  states.erase(state); 
}

InputMapping::GameInputMapper::GameInputMapper()
{
  unsigned countContexts;
	
  std::ifstream inputContextFile("ContextList.txt");
  countContexts = readDataTypeFromFile<unsigned>(inputContextFile);

  for(unsigned i = 0; i < countContexts; i++)
  {
    std::string name = readDataTypeFromFile<std::string>(inputContextFile);
    std::string file = readDataTypeFromFile<std::string>(inputContextFile);
    inputContexts[name] = new GameInputContext(file);
  }

  buttonPreviouslyPressed = InputMapping::RAW_INPUT_NO_BUTTON;
}

InputMapping::GameInputMapper::~GameInputMapper()
{
  for(std::map<std::string, GameInputContext*>::iterator iter = inputContexts.begin(); 
	                                                    iter != inputContexts.end(); iter++)
  {
    delete iter->second;
  }
}

void InputMapping::GameInputMapper::clearCurrentMappedInput()
{
  currentMappedInput.actions.clear();
}

void InputMapping::GameInputMapper::addCallback(inputCallback callback, int priorityInMultimap)
{
  callbackTable.insert(std::make_pair(priorityInMultimap, callback));
}

void InputMapping::GameInputMapper::dispatchInput(Player& player) const
{
  MappedInput input = currentMappedInput;

  for(std::multimap<int, inputCallback>::const_iterator iter = callbackTable.begin(); 
	                                                   iter != callbackTable.end(); iter++)
  {
    (*iter->second)(input, player);
  }
}

void InputMapping::GameInputMapper::pushContext(const std::string& name)
{
  std::map<std::string, GameInputContext*>::iterator iter = inputContexts.find(name);
  if( iter == inputContexts.end() )
  {
    throw std::exception("Invalid Input Context Pushed To List");
  }

  activeContexts.push_front(iter->second);
}

void InputMapping::GameInputMapper::popContext()
{
  if(activeContexts.empty())
  {
    throw std::exception("Cannot Pop Input Context Because There Is Not An Active Contexts");
  }

  activeContexts.pop_front();
}


void InputMapping::GameInputMapper::convertRawSDLToRawButtons(InputMapping::RawInputButton& button, 
	                                                          SDLKey pressedKey)
{
  switch(pressedKey)
  {
    case SDLK_LSHIFT:
    {
      button = InputMapping::RAW_INPUT_BUTTON_LSHIFT; 
      break;
    }
    case SDLK_RIGHT:  
    {
      button = InputMapping::RAW_INPUT_BUTTON_RIGHT;
      break;
    }
  }
}


void InputMapping::GameInputMapper::processNewInput(SDL_Event event)
{
  switch( event.type )
  {
	case SDL_KEYDOWN:
    {
      RawInputButton button;
      convertRawSDLToRawButtons(button, event.key.keysym.sym);
      setRawButtonState(button, true);
      break;
    }
	case SDL_KEYUP:
    {
      RawInputButton button;
      convertRawSDLToRawButtons(button, event.key.keysym.sym);
      setRawButtonState(button, false);
      break;
    }
	default:
    {
      break;
	}
  }
}

void InputMapping::GameInputMapper::setRawButtonState(InputMapping::RawInputButton button, bool isButtonPressed)
{
  Action action;
  State state;

  bool buttonWasPreviouslyPressed = false;

  if( isButtonPressed && !buttonWasPreviouslyPressed )
  {
    if( mapButtonToAction(button, action) )
    {
      currentMappedInput.actions.insert(action);
      buttonPreviouslyPressed = button;
      return;
    }
  }

  if( isButtonPressed )
  {
    if( mapButtonToState(button, state) )
    {
      currentMappedInput.states.insert(state);
      buttonPreviouslyPressed = button;
      return;
    }
  }

  if( isButtonPressed && buttonWasPreviouslyPressed )
  {
	buttonPreviouslyPressed = InputMapping::RAW_INPUT_NO_BUTTON;
    return;
  }

  mapAndEatButton(button);
}

bool InputMapping::GameInputMapper::mapButtonToAction(InputMapping::RawInputButton button, Action& action) const
{
  for(std::list<GameInputContext*>::const_iterator iter = activeContexts.begin(); iter != activeContexts.end(); iter++)
  {
    const GameInputContext* context = *iter;

    if( context->mapButtonToAction(button, action) )
    {
      return true;
    }
  }

  return false;
}

bool InputMapping::GameInputMapper::mapButtonToState(InputMapping::RawInputButton button, State& state) const
{
  for(std::list<GameInputContext*>::const_iterator iter = activeContexts.begin(); iter != activeContexts.end(); iter++)
  {
    const GameInputContext* context = *iter;

    if( context->mapButtonToState(button, state) )
    {
      return true;
    }
  }

  return false;
}

void InputMapping::GameInputMapper::mapAndEatButton(InputMapping::RawInputButton button)
{
  Action action;
  State state;

  if(mapButtonToAction(button, action))
  {
    currentMappedInput.eatAction(action);
  }

  if(mapButtonToState(button, state))
  {
    currentMappedInput.eatState(state);
  }
}



