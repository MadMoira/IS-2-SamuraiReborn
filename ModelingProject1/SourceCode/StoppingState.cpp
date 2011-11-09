
#include "StoppingState.h"

GameCoreStates::StoppingState::StoppingState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::StoppingState::~StoppingState(void)
{
}

int GameCoreStates::StoppingState::checkMovement(int keyPreviouslyPressed, int previousState,
	                                             int currentState, std::list<InputMapping::Key> keys)
{
  if( currentState == GameCoreStates::RUNNING )
  {
    return GameCoreStates::CHANGE;
  }

  return GameCoreStates::NO_CHANGE;
}