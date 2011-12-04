
#include "Controller.h"

#include <algorithm>


InputMapping::Controller::Controller(int id)
{
  playerID = id;
}

InputMapping::Controller::~Controller()
{
  keys.clear();  
  stateMap.clear();
}

void InputMapping::Controller::initializeKeys(std::list<Key> listKeys, 
	                           std::map<RawInputButton, GameCoreStates::SpriteState> mapKeys)
{
  keys = listKeys;
  stateMap = mapKeys;
}

InputMapping::Key& InputMapping::Controller::getKeyAssociatedToState(int state, int directionX)
{
  RawInputButton rawKey = RAW_INPUT_NO_BUTTON;

  if ( state == GameCoreStates::WALKING )
  {
	return getKeyDirectionX(directionX);
  }

  std::map<RawInputButton, GameCoreStates::SpriteState>::iterator iter = stateMap.begin();

  for (iter; iter != stateMap.end(); iter++)
  {
    if ( iter->second == state )
    {
      rawKey = iter->first;
      break;
    }
  }

  std::list<Key>::iterator iterKeys = keys.begin();

  for (iterKeys; iterKeys != keys.end(); iterKeys++)
  {
    if ( iterKeys->button == rawKey)
    {
	  return *iterKeys;
    }
  }

  return Key();
}

void InputMapping::Controller::setRawButtonState(InputMapping::Key key, InputMapping::MappedInput& inputs)
{
  GameCoreStates::SpriteState state;

  if( key.isPressed )
  {
    if( mapButtonToState(key.button, state) )
    {
      countAndClearStates(inputs);
      if ( verifyDoubleTappingForJumping(inputs, state) )
      {
        return;
      }
      pushBackNewState(inputs, state, key.button);
      return;
    }
  }

  if ( key.button == InputMapping::RAW_INPUT_NO_BUTTON && checkIfCanCleanStateVector(inputs) )
  {
    inputs.eatStates();
    if( mapButtonToState(key.button, state) )
    {
      pushBackNewState(inputs, state, key.button);
      return;
    }
  }
}

bool InputMapping::Controller::checkIfCanCleanStateVector(InputMapping::MappedInput& inputs)
{
  bool canClean = countStatesInMapper(inputs, GameCoreStates::JUMPING) != 1;
  canClean = canClean && countStatesInMapper(inputs, GameCoreStates::FAST_ATTACK) != 1; 
  return canClean;
}

void InputMapping::Controller::countAndClearStates(InputMapping::MappedInput& inputs)
{
  for (int i = GameCoreStates::WALKING; i <= GameCoreStates::JUMPING; i++)
  {
    if ( countStatesInMapper(inputs, i) > 1 )
    {
      inputs.eatStates();
      return;
    }
  }

  if ( countStatesInMapper(inputs, GameCoreStates::STILL) == 1 )
  {
    inputs.eatStates();
  }
}

int InputMapping::Controller::countStatesInMapper(InputMapping::MappedInput& inputs, int state)
{
  return count(inputs.states.begin(), inputs.states.end(), state);
}

bool InputMapping::Controller::verifyDoubleTappingForJumping(InputMapping::MappedInput& inputs, GameCoreStates::SpriteState state)
{
	if ( inputs.buttonPreviouslyPressed == getKeyAssociatedToState(GameCoreStates::JUMPING, 0).button &&
         state == GameCoreStates::JUMPING )
  {
    return true;
  }
  return false;
}

void InputMapping::Controller::pushBackNewState(InputMapping::MappedInput& inputs, int state, int valueButton)
{
  inputs.states.push_back(GameCoreStates::SpriteState(state));
  inputs.buttonPreviouslyPressed = valueButton;
}

bool InputMapping::Controller::mapButtonToState(InputMapping::RawInputButton button, 
                                               GameCoreStates::SpriteState& state) const
{
  std::map<RawInputButton, GameCoreStates::SpriteState>::const_iterator iter = stateMap.find(button);

  if( iter == stateMap.end() )
  {
    return false;
  }

  state = iter->second;
  return true;
}