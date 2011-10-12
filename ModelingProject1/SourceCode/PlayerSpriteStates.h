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
    FAST_ATTACK_WALKING,
  };

  enum ChangeStateResult
  {
    NO_CHANGE,
	CHANGE,
	RETURN_STILL,
  };
}