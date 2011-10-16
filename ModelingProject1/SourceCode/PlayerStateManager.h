#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "State.h"
#include "PlayerState.h"
#include "StillState.h"
#include "WalkingState.h"
#include "RunningState.h"
#include "JumpingState.h"
#include "DoubleJumpState.h"
#include "FastAttackWalkingState.h"

#include "PlayerSpriteStates.h"

#define STILL_STATE new GameCoreStates::StillState(GameCoreStates::STILL)
#define WALKING_STATE new GameCoreStates::WalkingState(GameCoreStates::WALKING)
#define JUMPING_STATE new GameCoreStates::JumpingState(GameCoreStates::JUMPING)
#define RUNNING_STATE new GameCoreStates::RunningState(GameCoreStates::RUNNING)
#define DOUBLE_JUMP_STATE new GameCoreStates::DoubleJumpState(GameCoreStates::DOUBLE_JUMP)
#define FAST_ATTACK_WALKING_STATE new GameCoreStates::FastAttackWalkingState(GameCoreStates::FAST_ATTACK_WALKING)

namespace GameCoreStates
{
  class PlayerStateManager
  {
    public:
	 PlayerStateManager(void);
	 ~PlayerStateManager(void);

	 void pushState( GameCoreStates::PlayerState* playerState );
	 void popState();
	 void changeState( GameCoreStates::PlayerState* newState );

	 int getCurrentState() { return currentState.getCurrentID(); }
	 int getPreviousState() { return previousState; }

    private:
	 boost::ptr_vector< State > statesStack;
	 GameCoreStates::SpriteState previousState;
	 GameCoreStates::PlayerState currentState;
  };
}

