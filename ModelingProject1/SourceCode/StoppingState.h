#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class StoppingState : public PlayerState
  {
   public:
    StoppingState(int id);
    ~StoppingState(void);

    int checkMovement(int keyPreviouslyPressed, int previousState, 
		              int currentState, std::list<InputMapping::Key> keys);
  };
}

