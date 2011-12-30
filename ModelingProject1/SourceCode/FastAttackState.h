#pragma once
#include "playerstate.h"

namespace GameCoreStates
{
  class FastAttackState : public PlayerState
  {
    public:
	// FastAttackState(int id);
	 FastAttackState(int id, int charID);
	 ~FastAttackState(void);

	 int checkMovement(int keyPreviouslyPressed, int previousState, 
		              int currentState, std::list<InputMapping::Key> keys);

  };
}
