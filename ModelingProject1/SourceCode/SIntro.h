#pragma once

#include "GameState.h"

class SIntro : public GameState
{
  public:
   SIntro( GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName );
   ~SIntro();

   void init();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();

  private:
   Image::GameImage* logoGameImage;
   Uint32 framerate;
};

