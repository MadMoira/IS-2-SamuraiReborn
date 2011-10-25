
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
  GameCoreStates::ConditionsPlayerRunning isRunning = checkIfPlayerIsRunning(keys);


  if ( currentState == GameCoreStates::RUNNING && isRunning.directionButtonPressed && 
	  isRunning.runningButtonPressed )
  {
	  return GameCoreStates::NO_CHANGE;
  }

  if ( (currentState == GameCoreStates::WALKING || currentState == GameCoreStates::STILL ||
	  ( currentState == GameCoreStates::FAST_ATTACK && keyPreviouslyPressed == 1 )
	  || previousState == GameCoreStates::JUMPING) && isRunning.directionButtonPressed && 
	  isRunning.runningButtonPressed)
  {
    return GameCoreStates::CHANGE;
  }

  if ( isRunning.runningButtonPressed && !isRunning.directionButtonPressed )
  {
    return GameCoreStates::RETURN_STILL;
  }

  return GameCoreStates::NO_CHANGE;
}

int GameCoreStates::RunningState::checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
		                   int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed)
{
  return checkMovement(keyPreviouslyPressed, previousState, currentState, keys);
}
