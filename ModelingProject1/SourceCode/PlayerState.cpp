#include "PlayerState.h"

GameCoreStates::PlayerState::PlayerState(int id) : State( id )
{
  currentID = id;
}

int GameCoreStates::PlayerState::checkMovement(int keyPreviouslyPressed, int previousState, 
	                           int currentState, std::list<InputMapping::Key> keys)
{
  return GameCoreStates::NO_CHANGE;
}

int GameCoreStates::PlayerState::checkMovementRestrictions(int keyPreviouslyPressed, int previousState, 
	                                        int currentState, std::list<InputMapping::Key> keys)
{
  return checkMovement(keyPreviouslyPressed, previousState, currentState, keys);
}