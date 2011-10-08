#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class WalkingState : public PlayerState
  {
   public:
	WalkingState(int id);
	~WalkingState(void);

	int checkMovement(int keyPreviouslyPressed, int previousState, 
		              int currentState, std::list<InputMapping::Key> keys);
  };
}

