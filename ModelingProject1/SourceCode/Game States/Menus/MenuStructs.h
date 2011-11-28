#pragma once

#include "GameImage.h"

namespace Image
{
  struct ArrowMenu
  {
    GameImage* arrow;
    int optionSelected;

	virtual void updatePositionArrow() = 0;
  };

  struct ArrowMainMenu : ArrowMenu
  {
	void updatePositionArrow();
  };

  struct ArrowSelectMenu : ArrowMenu
  {
	void updatePositionArrow();
  };
}

namespace Image
{
  struct ControllerSelection
  {
    GameImage* controller;
    int selectedPlayer;

    void updatePositionController();
  };

  struct CustomCursor
  {
    GameImage* cursor;
  };
}
