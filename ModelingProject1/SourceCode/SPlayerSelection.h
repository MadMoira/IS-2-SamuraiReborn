#pragma once

#include "GameState.h"

class SPlayerSelection : public GameState
{
  public:
   SPlayerSelection( GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName );
   ~SPlayerSelection(void);

   void init();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();
};

