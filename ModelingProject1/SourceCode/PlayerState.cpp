#include "PlayerState.h"

GameCoreStates::PlayerState::PlayerState(int id) : State( id )
{
  currentID = id;
}

int GameCoreStates::PlayerState::checkIfEqualStates(std::list<InputMapping::Key> keys, int currentState,
	                                                int previousState, GameCoreStates::PlayerState* newState)
{
  return checkChangeOfState(keys, currentState, previousState, newState);
}

int GameCoreStates::PlayerState::checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
		                                            int previousState, GameCoreStates::PlayerState* newState)
{
  if ( currentState == newState->getCurrentID() )
  {
    return GameCoreStates::NO_CHANGE;
  }
  
  return GameCoreStates::CHANGE;
}

int GameCoreStates::PlayerState::checkMovementRestrictions(int keyPreviouslyPressed, int previousState, 
	                                        int currentState, std::list<InputMapping::Key> keys)
{
  return checkMovement(keyPreviouslyPressed, previousState, currentState, keys);
}

int GameCoreStates::PlayerState::checkMovement(int keyPreviouslyPressed, int previousState, 
	                           int currentState, std::list<InputMapping::Key> keys)
{
  return GameCoreStates::NO_CHANGE;
}

