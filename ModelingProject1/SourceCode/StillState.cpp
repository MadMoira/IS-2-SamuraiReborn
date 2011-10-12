
#include "StillState.h"

GameCoreStates::StillState::StillState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::StillState::~StillState(void)
{
}

int GameCoreStates::StillState::checkMovement(int keyPreviouslyPressed, int previousState,
	                                          int currentState, std::list<InputMapping::Key> keys)
{
  return GameCoreStates::CHANGE;
}