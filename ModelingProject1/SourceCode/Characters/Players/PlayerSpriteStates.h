#pragma once

namespace GameCoreStates
{
  enum GameStates 
  {
    STATE_NULL,
    STATE_INTRO, 
    STATE_MAINMENU, 
    STATE_MENUSELECTIONPLAYER,
    STATE_LEVELZEROTUTORIAL, 
    STATE_LEVELONEJAPAN,
    STATE_EXIT,
  };

  enum SpriteState
  {
    STILL,
    WALKING,
    JUMPING,
    RUNNING,
    DOUBLE_JUMP,
    FAST_ATTACK,
    FALLING,
  };

  enum Action
  {
	RIGHT,
	LEFT,
	CONTINUE,
	BACK,
	UP,
	DOWN,
  };

  enum ChangeStateResult
  {
    NO_CHANGE,
    CHANGE,
    UPDATE_SPEEDX,
  };
}