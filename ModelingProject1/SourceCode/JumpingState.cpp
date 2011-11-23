
#include <algorithm>
#include "ComparatorFunctions.h"

#include "JumpingState.h"

GameCoreStates::JumpingState::JumpingState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::JumpingState::~JumpingState(void)
{
}

int GameCoreStates::JumpingState::checkMovement(int keyPreviouslyPressed, int previousState, 
                                                int currentState, std::list<InputMapping::Key> keys)
{
  InputMapping::Key findKey = *std::find_if(keys.begin(), keys.end(), isJumpingKeyPressed);
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(keys);
  bool jumpingButtonIsPressed = findKey.isPressed;

  if ( keyPreviouslyPressed != InputMapping::RAW_INPUT_NO_BUTTON && !jumpingButtonIsPressed )
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( jumpingButtonIsPressed && findKey.wasPreviouslyPressed )
  {
    return GameCoreStates::NO_CHANGE;
  }

  if ( ( currentState != GameCoreStates::JUMPING  && currentState != GameCoreStates::DOUBLE_JUMP
                                                  && currentState != GameCoreStates::FALLING
                                                  && currentState != GameCoreStates::FAST_ATTACK ) || 
       ( previousState == GameCoreStates::JUMPING && currentState == GameCoreStates::STILL ) )
  {
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}

int GameCoreStates::JumpingState::checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
                           int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed)
{
  InputMapping::Key findKey = *std::find_if(keys.begin(), keys.end(), isJumpingKeyPressed);
  GameCoreStates::ConditionsPlayerRunning isPacing = checkIfPlayerIsRunning(keys);
  bool jumpingButtonIsPressed = findKey.isPressed;

  if ( currentState == GameCoreStates::JUMPING && isPacing.directionButtonPressed && !isPacing.runningButtonPressed)
  {
    return GameCoreStates::UPDATE_SPEEDX;
  }

  if ( currentState != previousState)
  {
    return GameCoreStates::CHANGE;
  }
  return GameCoreStates::NO_CHANGE;
}
