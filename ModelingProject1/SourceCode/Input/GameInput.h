#pragma once

#include "GameInputMapper.h"

class GameInput
{
  public:
   GameInput(void);
   ~GameInput(void);

   bool handleWindowEvents();
   void handleKeyEvents(InputMapping::GameInputMapper* gameInputMapper, InputMapping::Controller* controller);
};

