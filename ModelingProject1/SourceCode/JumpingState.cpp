
#include <algorithm>

#include "JumpingState.h"

#include "ComparatorFunctions.h"


GameCoreStates::JumpingState::JumpingState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::JumpingState::~JumpingState(void)
{
}

int GameCoreStates::JumpingState::checkMovement(int keyPreviouslyPressed, int previousState, int currentState, std::list<InputMapping::Key> keys)
{
  InputMapping::Key findKey = *std::find_if(keys.begin(), keys.end(), isJumpingKeyPressed);
  bool jumpingButtonIsPressed = findKey.isPressed;

  if ( keyPreviouslyPressed != InputMapping::RAW_INPUT_NO_BUTTON && !jumpingButtonIsPressed )
  {
	  return GameCoreStates::NO_CHANGE;
  }

  if ( (currentState != GameCoreStates::JUMPING && currentState != GameCoreStates::DOUBLE_JUMP) ||
	   (previousState == GameCoreStates::JUMPING && currentState == GameCoreStates::STILL) )
  {
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}
