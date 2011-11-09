
#include <algorithm>
#include <fstream>

#include "SpriteDataConstants.h"
#include "GameInputMapper.h"
#include "GameInputContext.h"
#include "File.h"

#include "ComparatorFunctions.h"

void InputMapping::MappedInput::eatAction(GameCoreStates::Action action)
{
  actions.erase(action); 
}

void InputMapping::MappedInput::eatStates()
{
  states.clear();
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

  currentMappedInput.buttonPreviouslyPressed = InputMapping::RAW_INPUT_NO_BUTTON;
  currentMappedInput.directionKeyPressed = SpriteData::RIGHT;
}

InputMapping::GameInputMapper::~GameInputMapper()
{
  for(std::map<std::string, GameInputContext*>::iterator iter = inputContexts.begin(); 
	                                                    iter != inputContexts.end(); iter++)
  {
    delete iter->second;
  }
}

void InputMapping::GameInputMapper::clearCurrentMappedInput(GameCoreStates::SpriteState activeState)
{
  currentMappedInput.actions.clear();

  if ( !currentMappedInput.states.empty() )
  {
    if (activeState == GameCoreStates::DOUBLE_JUMP || activeState == GameCoreStates::FALLING)
    {
      activeState = GameCoreStates::JUMPING;
    }

    currentMappedInput.states.clear();
    currentMappedInput.states.push_back(activeState);
  }
}

void InputMapping::GameInputMapper::addCallback(inputCallback callback, int priorityInMultimap)
{
  callbackTable.insert(std::make_pair(priorityInMultimap, callback));
}

void InputMapping::GameInputMapper::dispatchInput(Player& player) const
{
  MappedInput input = currentMappedInput;
  std::list<InputMapping::Key> keys = getListKeys();

  for(std::multimap<int, inputCallback>::const_iterator iter = callbackTable.begin(); 
	                                                   iter != callbackTable.end(); iter++)
  {
    (*iter->second)(input, player, keys);
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

void InputMapping::GameInputMapper::convertRawSDLToRawButtons(InputMapping::Key& key)
{
  switch(key.button)
  {
    case SDLK_LSHIFT:
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_LSHIFT; 
      break;
    }
    case SDLK_RIGHT:  
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_RIGHT;

	  if ( key.isPressed )
	  {
        currentMappedInput.directionKeyPressed = SpriteData::RIGHT; 
	  }
	  
      break;
    }
    case SDLK_LEFT:  
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_LEFT;

	  if ( key.isPressed )
	  {
        currentMappedInput.directionKeyPressed = SpriteData::LEFT; 
	  }

      break;
    }
	case SDLK_z:
	{
      key.button = InputMapping::RAW_INPUT_BUTTON_Z; 
      break;
	}

	case SDLK_x:
	{
      key.button = InputMapping::RAW_INPUT_BUTTON_X; 
      break;
	}

  }
}

void InputMapping::GameInputMapper::processNewInput()
{
  Uint8 *keystate = SDL_GetKeyState(NULL);
  returnKeyForMappedInput(keystate);
}

void InputMapping::GameInputMapper::setRawButtonState(InputMapping::Key key)
{
  GameCoreStates::Action action;
  GameCoreStates::SpriteState state;

  bool buttonWasPreviouslyPressed = false;

  if( key.isPressed && !buttonWasPreviouslyPressed )
  {
    if( mapButtonToAction(key.button, action) )
    {
      currentMappedInput.actions.insert(action);
      currentMappedInput.buttonPreviouslyPressed = key.button;
      return;
    }
  }

  if( key.isPressed )
  {
    if( mapButtonToState(key.button, state) )
    {
	  countAndClearStates();
	  if ( verifyDoubleTappingForJumping(state) )
      {
        return;
      }
	  pushBackNewState(state, key.button);
      return;
    }
  }

  if ( key.button == InputMapping::RAW_INPUT_NO_BUTTON && checkIfCanCleanStateVector() )
  {
    currentMappedInput.eatStates();
    if( mapButtonToState(key.button, state) )
	{
      pushBackNewState(state, key.button);
      return;
    }
  }
}

bool InputMapping::GameInputMapper::checkIfCanCleanStateVector()
{
  bool canClean = countStatesInMapper(GameCoreStates::JUMPING) != 1;
  canClean = canClean && countStatesInMapper(GameCoreStates::FAST_ATTACK) != 1; 
  return canClean;
}

void InputMapping::GameInputMapper::countAndClearStates()
{
  for (int i = GameCoreStates::WALKING; i <= GameCoreStates::JUMPING; i++)
  {
    if ( countStatesInMapper(i) > 1 )
    {
      currentMappedInput.eatStates();
	  return;
	}
  }

  if ( countStatesInMapper(GameCoreStates::STILL) == 1 )
  {
    currentMappedInput.eatStates();
  }
}

int InputMapping::GameInputMapper::countStatesInMapper(int state)
{
  return count(currentMappedInput.states.begin(), currentMappedInput.states.end(), state);
}

bool InputMapping::GameInputMapper::verifyDoubleTappingForJumping(GameCoreStates::SpriteState state)
{
  if ( currentMappedInput.buttonPreviouslyPressed == InputMapping::RAW_INPUT_BUTTON_LSHIFT &&
       state == GameCoreStates::JUMPING )
  {
    return true;
  }
  return false;
}

void InputMapping::GameInputMapper::pushBackNewState(int state, int valueButton)
{
  currentMappedInput.states.push_back(GameCoreStates::SpriteState(state));
  currentMappedInput.buttonPreviouslyPressed = valueButton;
}

void InputMapping::GameInputMapper::returnKeyForMappedInput(Uint8* keystate) 
{
  InputMapping::GameInputContext* gameInputActiveContext = activeContexts.front();
  std::list<InputMapping::Key>* keys = gameInputActiveContext->getKeysList();
  std::list<InputMapping::Key>::iterator iter = keys->begin();
  
  iter++;

  bool anyKeyIsPressed = false;

  for ( iter; iter != keys->end(); iter++)
  {
	bool keyStateIterButton = checkKeyState(keystate[iter->button]);
    if( !iter->isPressed && keyStateIterButton )
    {
      iter->isPressed = true;
	  iter->isReleased = false;
	  iter->wasPreviouslyPressed = false;
	  anyKeyIsPressed = true;
    }
    else if( iter->isPressed && !keyStateIterButton )
    {
      iter->isPressed = false;
      iter->isReleased = true;
	  iter->wasPreviouslyPressed = true;
    }
	else
	{
	  if ( iter->isPressed = keyStateIterButton )
	  {
        anyKeyIsPressed = true;
	  }

      iter->isReleased = false;  
	  iter->wasPreviouslyPressed = true;
	}

	convertRawSDLToRawButtons(*iter);
	setRawButtonState(*iter);
  }

  if ( !anyKeyIsPressed )
  {
	iter = keys->begin();
    convertRawSDLToRawButtons(*iter);
	setRawButtonState(*iter);
  }
}

bool InputMapping::GameInputMapper::checkKeyState(Uint8 key)
{
  if ( key )
  {
    return true;
  }

  return false;
}

std::list<InputMapping::Key> InputMapping::GameInputMapper::getListKeys() const
{
  InputMapping::GameInputContext* gameInputActualContext = activeContexts.front();
  return *gameInputActualContext->getKeysList();
}

void InputMapping::GameInputMapper::pushBackStateOnMappedInput(GameCoreStates::SpriteState newState)
{
  currentMappedInput.states.push_back(newState);
}

bool InputMapping::GameInputMapper::mapButtonToAction(InputMapping::RawInputButton button, 
	                                                 GameCoreStates::Action& action) const
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

bool InputMapping::GameInputMapper::mapButtonToState(InputMapping::RawInputButton button, 
	                                                GameCoreStates::SpriteState& state) const
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




