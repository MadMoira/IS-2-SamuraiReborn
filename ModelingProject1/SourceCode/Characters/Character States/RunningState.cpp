
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
  const int RETURNING_FROM_PREVIOUS_STATE = 1;

  if ( ( currentState == GameCoreStates::RUNNING || currentState == GameCoreStates::FAST_ATTACK ) &&
         isRunning.directionButtonPressed && isRunning.runningButtonPressed && 
         keyPreviouslyPressed != RETURNING_FROM_PREVIOUS_STATE  )
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( ( currentState == GameCoreStates::WALKING || currentState == GameCoreStates::STILL ||
       ( currentState == GameCoreStates::FAST_ATTACK && keyPreviouslyPressed == RETURNING_FROM_PREVIOUS_STATE ) ||
         previousState == GameCoreStates::JUMPING ) && 
         isRunning.directionButtonPressed && isRunning.runningButtonPressed )
  {
    return GameCoreStates::CHANGE;
  }

  if ( currentState == GameCoreStates::FAST_ATTACK && previousState == GameCoreStates::JUMPING && 
       keyPreviouslyPressed != RETURNING_FROM_PREVIOUS_STATE)
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( !isRunning.runningButtonPressed && isRunning.directionButtonPressed && 
       keyPreviouslyPressed == RETURNING_FROM_PREVIOUS_STATE)
  {
    return GameCoreStates::RETURN_WALKING;
  }

  if ( isRunning.runningButtonPressed && !isRunning.directionButtonPressed && 
       currentState != GameCoreStates::STILL)
  {
    return GameCoreStates::RETURN_STILL;
  }

  if ( keyPreviouslyPressed == 5 )
  {
	  return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}

int GameCoreStates::RunningState::checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
                           int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed)
{
  return checkMovement(keyPreviouslyPressed, previousState, currentState, keys);
}
