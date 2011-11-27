#include "FallingState.h"

GameCoreStates::FallingState::FallingState(int id) : PlayerState( id )
{
  currentID = id;
}

GameCoreStates::FallingState::~FallingState(void)
{
}

int GameCoreStates::FallingState::checkMovement(int keyPreviouslyPressed, int previousState, 
	                                            int currentState, std::list<InputMapping::Key> keys)
{
  return CHANGE;
}
