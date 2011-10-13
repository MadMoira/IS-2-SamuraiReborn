
#include <algorithm>

#include "DoubleJumpState.h"

#include "ComparatorFunctions.h"

GameCoreStates::DoubleJumpState::DoubleJumpState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::DoubleJumpState::~DoubleJumpState(void)
{
}

int GameCoreStates::DoubleJumpState::checkMovement(int keyPreviouslyPressed, int previousState, int currentState, 
	std::list<InputMapping::Key> keys)
{
  InputMapping::Key findKey = *std::find_if(keys.begin(), keys.end(), isJumpingKeyPressed);
  bool jumpingButtonIsPressed = findKey.isPressed;

  if ( currentState == GameCoreStates::JUMPING && previousState != GameCoreStates::DOUBLE_JUMP && 
	   keyPreviouslyPressed == InputMapping::RAW_INPUT_NO_BUTTON && jumpingButtonIsPressed)
  {
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}
