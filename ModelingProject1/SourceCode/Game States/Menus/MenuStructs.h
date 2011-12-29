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
  struct PlayersInitialize
  {
	int characterID;
	int controllerID;
  };

  struct CustomCursor
  {
    GameImage* cursor;
  };
}
