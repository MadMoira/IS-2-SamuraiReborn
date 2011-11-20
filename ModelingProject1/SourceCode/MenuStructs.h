#pragma once

#include <CEGUI.h>
#include "GameImage.h"

namespace MenuStructs
{
  struct MenuButton
  {
    CEGUI::PushButton* button;
    int id;
  };
}

namespace Image
{
  struct ArrowMainMenu
  {
    GameImage* arrow;
    int optionSelected;

	void updatePositionArrow();
  };
}