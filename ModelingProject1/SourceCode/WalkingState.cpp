
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
  if( currentState == GameCoreStates::DOUBLE_JUMP)
  {
    return GameCoreStates::NO_CHANGE;
  }

  return GameCoreStates::CHANGE;
}