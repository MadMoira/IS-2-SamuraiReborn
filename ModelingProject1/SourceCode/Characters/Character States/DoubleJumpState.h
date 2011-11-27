#pragma once

#include "PlayerState.h"

namespace GameCoreStates
{
  class DoubleJumpState : public PlayerState
  {
   public:
    DoubleJumpState(int id);
    ~DoubleJumpState(void);

    int checkMovement(int keyPreviouslyPressed, int previousState, 
                      int currentState, std::list<InputMapping::Key> keys);
    int checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
                           int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed);
  };
}