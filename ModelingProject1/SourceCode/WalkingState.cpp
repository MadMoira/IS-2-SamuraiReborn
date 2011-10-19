
#include <algorithm>
#include "ComparatorFunctions.h"

#include "WalkingState.h"

GameCoreStates::WalkingState::WalkingState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::WalkingState::~WalkingState(void)
{
}

int GameCoreStates::WalkingState::checkMovement(int keyPreviouslyPressed, int previousState, 
                                                int currentState, std::list<InputMapping::Key> keys)
{
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(keys);

  if ( currentState == GameCoreStates::RUNNING && isPacing.directionButtonPressed 
	   && !isPacing.runningButtonPressed )
  {
    return GameCoreStates::CHANGE;
  }

  if( (currentState == GameCoreStates::DOUBLE_JUMP || currentState == GameCoreStates::FAST_ATTACK || 
	  currentState == GameCoreStates::RUNNING) && keyPreviouslyPressed != InputMapping::RAW_INPUT_NO_BUTTON )
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( !isPacing.directionButtonPressed )
  {
    return GameCoreStates::RETURN_STILL;
  }

  return GameCoreStates::CHANGE;
}
