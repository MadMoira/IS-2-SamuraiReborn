
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

  if ( !isPacing.directionButtonPressed && ( currentState == GameCoreStates::WALKING ||
	                                         currentState == GameCoreStates::RUNNING ) )
  {
	return GameCoreStates::RETURN_STILL;
  }

  if ( (currentState != GameCoreStates::DOUBLE_JUMP && currentState != GameCoreStates::FALLING) &&
	   keyPreviouslyPressed == InputMapping::RAW_INPUT_NO_BUTTON && fastAttackButtonIsPressed )
  {

    GameSound::getInstance()->loadChunk(0/*currentID*/,0);
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}