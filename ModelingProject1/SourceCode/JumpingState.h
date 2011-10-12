#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class JumpingState : public PlayerState
  {
   public:
    JumpingState(int id);
    ~JumpingState(void);

    int checkMovement(int keyPreviouslyPressed, int previousState, 
		              int currentState, std::list<InputMapping::Key> keys);
  };
}
