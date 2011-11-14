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
	FAST_ATTACK,
	FALLING,
	STOPPING,
  };

  enum Action
  {
  };

  enum ChangeStateResult
  {
    NO_CHANGE,
	CHANGE,
	RETURN_STILL,
	RETURN_STOPPING,
	RETURN_WALKING,
	UPDATE_SPEEDX,
  };
}