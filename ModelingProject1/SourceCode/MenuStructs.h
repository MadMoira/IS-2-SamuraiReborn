#pragma once

#include "GameImage.h"

namespace Image
{
  struct ArrowMainMenu
  {
    GameImage* arrow;
    int optionSelected;

    void updatePositionArrow();
  };

  struct ControllerSelection
  {
	GameImage* controller;
	int selectedPlayer;

	void updatePositionController();
  };
}
