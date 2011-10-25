#pragma once

#include "GameState.h"

#include "Level.h"
#include "AI.h"

class SLevelOneJapan : public GameState
{
  public:
   SLevelOneJapan( GameRender* gR, GameCore* gC, GameInput* gI, GamePhysics::PhysicsCore* gP, GameStates stateName );
   ~SLevelOneJapan();

   void init();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();
   void checkGravity(int vPosition);

  private:
   Level* japanLevel;
   AI levelAI;
};

