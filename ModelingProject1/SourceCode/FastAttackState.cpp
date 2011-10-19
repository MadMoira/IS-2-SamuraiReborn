
#include <algorithm>

#include "ComparatorFunctions.h"

#include "FastAttackState.h"


GameCoreStates::FastAttackState::FastAttackState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::FastAttackState::~FastAttackState(void)
{
}

int GameCoreStates::FastAttackState::checkMovement(int keyPreviouslyPressed, int previousState, 
                                                int currentState, std::list<InputMapping::Key> keys)
{
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(keys);
  InputMapping::Key findKey = *std::find_if(keys.begin(), keys.end(), isFastAttackKeyPressed);
  bool fastAttackButtonIsPressed = findKey.isPressed;

  if ( !isPacing.directionButtonPressed )
  {
	return GameCoreStates::RETURN_STILL;
  }

  if ( (currentState == GameCoreStates::WALKING || currentState == GameCoreStates::JUMPING)
	  && keyPreviouslyPressed == InputMapping::RAW_INPUT_NO_BUTTON 
	  && fastAttackButtonIsPressed )
  {
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}