
#include <algorithm>

#include "PlayerState.h"
#include "ComparatorFunctions.h"

GameCoreStates::PlayerState::PlayerState(int id) : State( id )
{
  currentID = id;
}

int GameCoreStates::PlayerState::checkIfEqualStates(std::list<InputMapping::Key> keys, int currentState,
	                                                int previousState, GameCoreStates::PlayerState* newState,
													int keyPreviouslyPressed)
{
  return checkChangeOfState(keys, currentState, previousState, newState, keyPreviouslyPressed);
}

int GameCoreStates::PlayerState::checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
		                                            int previousState, GameCoreStates::PlayerState* newState,
													int keyPreviouslyPressed)
{
  if ( currentState == newState->getCurrentID() )
  {
    return GameCoreStates::NO_CHANGE;
  }
  
  return GameCoreStates::CHANGE;
}

GameCoreStates::ConditionsPlayerRunning GameCoreStates::PlayerState::checkIfPlayerIsRunning(
	                                        std::list<InputMapping::Key> keys)
{
  bool directionButtonPressed = false;
  bool directionButtonRightPressed = false;
  bool directionButtonLeftPressed = false;
  bool runningButtonPressed = false;

  GameCoreStates::ConditionsPlayerRunning isRunning;

  InputMapping::Key findKey = *std::find_if(keys.begin(), keys.end(), isWalkingKeyRightPressed);
  directionButtonRightPressed = findKey.isPressed;

  findKey = *std::find_if(keys.begin(), keys.end(), isWalkingKeyLeftPressed);
  directionButtonLeftPressed = findKey.isPressed;

  findKey = *std::find_if(keys.begin(), keys.end(), isRunningKeyPressed);
  isRunning.runningButtonPressed = findKey.isPressed;

  isRunning.directionButtonPressed = directionButtonRightPressed || directionButtonLeftPressed;

  return isRunning;
}

int GameCoreStates::PlayerState::checkMovementRestrictions(int keyPreviouslyPressed, int previousState, 
	                                        int currentState, std::list<InputMapping::Key> keys)
{
  return checkMovement(keyPreviouslyPressed, previousState, currentState, keys);
}

int GameCoreStates::PlayerState::checkMovement(int keyPreviouslyPressed, int previousState, 
	                           int currentState, std::list<InputMapping::Key> keys)
{
  if ( currentState != previousState)
  {
    return GameCoreStates::CHANGE;
  }
  return GameCoreStates::NO_CHANGE;
}

