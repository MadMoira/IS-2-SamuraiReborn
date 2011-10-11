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
  };

  enum Action
  {
    FAST_ATTACK,
    STRONG_ATTACK,
    MELEE_ATTACK,
  };

  enum ChangeStateResult
  {
    NO_CHANGE,
	CHANGE,
	RETURN_STILL,
  };
}