


#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"
#include "MovementPhys.h"

#include "GameStateManager.h"

#include "SLevelTutorial.h"

int main( int argc, char* args[] )
{
  GameCore Core;
  GameRender Render;
  GameInput Input;
  GameStateManager *StateManager = new GameStateManager();
  MovementPhys ff(8);
	
  if( !Core.initializeGameCore() )
  {
    return 1;
  }

  StateManager->changeState( new SLevelTutorial( &Render, &Core, &Input, STATE_LEVELZEROTUTORIAL ) );
	
  StateManager->init();

  while( Core.getIsRunning() )
  {
    Core.getGameTimer()->start();

    StateManager->handleEvents();
    StateManager->logic();
    StateManager->render();

    Core.getGameTimer()->delay();
  }
	
  delete StateManager;
  Core.cleanUpGameCore();

  return 0;
}
