
#include "StillState.h"

GameCoreStates::StillState::StillState(int id)//, int charID)
{
 // characterID = charID;
  currentID = id;
}


GameCoreStates::StillState::~StillState(void)
{
}

int GameCoreStates::StillState::checkMovement(int keyPreviouslyPressed, int previousState,
	                                          int currentState, std::list<InputMapping::Key> keys)
{
  if ( currentState == GameCoreStates::STOPPING )
  {
    return GameCoreStates::NO_CHANGE;
  }
  return GameCoreStates::CHANGE;
}