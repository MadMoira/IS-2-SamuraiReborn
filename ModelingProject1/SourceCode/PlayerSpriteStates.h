#pragma once

namespace GameCoreStates
{
  enum SpriteState
  {
    STILL,
	WALKING,
	JUMPING,
	RUNNING,
    DOUBLE_JUMP,
	FAST_ATTACK_WALKING,
  };

  enum Action
  {
    FAST_ATTACK,
  };

  enum ChangeStateResult
  {
    NO_CHANGE,
	CHANGE,
	RETURN_STILL,
  };
}