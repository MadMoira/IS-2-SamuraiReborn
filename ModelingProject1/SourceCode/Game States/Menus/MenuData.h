#pragma once

namespace MenuData
{
  enum MainMenuOptions
  {
    NOTHING_SELECTED,
    HISTORY_MODE,
    TUTORIAL,
    CREDITS,
    QUIT,
  };

  enum SelectPlayer
  {
	PLAYER_ONE,
	NO_SELECTED_PLAYER,
	PLAYER_TWO,
	CONTINUE,
	BACK,
  };

  enum PauseOptions
  {
	CONTINUE_GAME = 1,
	SOUND,
	MAIN_MENU,
  };
}