
#include <algorithm>

#include "RunningState.h"

#include "PlayerSpriteStates.h"

#include "ComparatorFunctions.h"


GameCoreStates::RunningState::RunningState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::RunningState::~RunningState(void)
{
}

int GameCoreStates::RunningState::checkMovement(int keyPreviouslyPressed, int previousState, 
	                                            int currentState, std::list<InputMapping::Key> keys)
{
  bool directionButtonPressed = false;
  bool directionButtonRightPressed = false;
  bool directionButtonLeftPressed = false;
  bool runningButtonPressed = false;

  InputMapping::Key findKey = *std::find_if(keys.begin(), keys.end(), isWalkingKeyRightPressed);
  directionButtonRightPressed = findKey.isPressed;

  findKey = *std::find_if(keys.begin(), keys.end(), isWalkingKeyLeftPressed);
  directionButtonLeftPressed = findKey.isPressed;

  findKey = *std::find_if(keys.begin(), keys.end(), isRunningKeyPressed);
  runningButtonPressed = findKey.isPressed;

  directionButtonPressed = directionButtonRightPressed || directionButtonLeftPressed;

  if ( (currentState == GameCoreStates::WALKING || currentState == GameCoreStates::STILL 
	  || previousState == GameCoreStates::JUMPING) && directionButtonPressed && runningButtonPressed)
  {
    return GameCoreStates::CHANGE;
  }

  if ( runningButtonPressed && !directionButtonPressed )
  {
    return GameCoreStates::RETURN_STILL;
  }

  return GameCoreStates::NO_CHANGE;
}

int GameCoreStates::RunningState::checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
		                   int previousState, GameCoreStates::PlayerState* newState)
{
  return checkMovement(0, previousState, currentState, keys);
}
