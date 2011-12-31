#pragma once

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"

#include <GameStatesData.h>

class GameState
{
  public:
   virtual void init() { };
   virtual void resume() { };
   virtual void handleEvents() { };
   virtual void logic() { };
   virtual void render() { };
   virtual void cleanUp() { };
   virtual ~GameState() { };

   MainStates::GameStates getNameState() { return nameState; }

   int checkIfStateEnd() { return hasEnded; }
   void setHasEnded(int stateHasEnded) { hasEnded = stateHasEnded; }

  private:
   int hasEnded;

  protected:
   GameState( GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName );
   GameRender* gameRender;
   GameCore* gameCore;
   GameInput* gameInput;
   MainStates::GameStates nameState;
};

