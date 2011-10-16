
#include <algorithm>

#include "ComparatorFunctions.h"

#include "FastAttackWalkingState.h"


GameCoreStates::FastAttackWalkingState::FastAttackWalkingState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::FastAttackWalkingState::~FastAttackWalkingState(void)
{
}

int GameCoreStates::FastAttackWalkingState::checkMovement(int keyPreviouslyPressed, int previousState, 
                                                int currentState, std::list<InputMapping::Key> keys)
{
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(keys);
  InputMapping::Key findKey = *std::find_if(keys.begin(), keys.end(), isFastAttackKeyPressed);
  bool fastAttackButtonIsPressed = findKey.isPressed;

  if ( !isPacing.directionButtonPressed )
  {
	return GameCoreStates::RETURN_STILL;
  }

  if ( currentState == GameCoreStates::WALKING && keyPreviouslyPressed == InputMapping::RAW_INPUT_NO_BUTTON 
	  && fastAttackButtonIsPressed )
  {
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}