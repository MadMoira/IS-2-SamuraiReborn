#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class RunningState : public PlayerState
  {
   public:
	RunningState(int id);
	~RunningState(void);

	int checkMovement(int keyPreviouslyPressed, int previousState, 
		              int currentState, std::list<InputMapping::Key> keys);
    int checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
		                   int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed);
  };
}
