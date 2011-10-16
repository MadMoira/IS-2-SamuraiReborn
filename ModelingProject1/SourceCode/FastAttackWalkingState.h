#pragma once
#include "playerstate.h"

namespace GameCoreStates
{
  class FastAttackWalkingState : public PlayerState
  {
    public:
	 FastAttackWalkingState(int id);
	 ~FastAttackWalkingState(void);

	 int checkMovement(int keyPreviouslyPressed, int previousState, 
		              int currentState, std::list<InputMapping::Key> keys);
  };
}
