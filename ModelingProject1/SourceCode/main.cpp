

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"

#include "GameStateManager.h"

#include "SLevelTutorial.h"
#include "SMainMenu.h"

int main( int argc, char* args[] )
{
  GameCore Core;
  GameRender Render;
  GameInput Input;
  GameStateManager *StateManager = new GameStateManager();
	
  if( !Core.initializeGameCore() )
  {
    return 1;
  }

  StateManager->changeState( new SMainMenu( &Render, &Core, &Input, STATE_MAINMENU ) );
  StateManager->init();

  while( Core.getIsRunning() )
  {
    StateManager->changeCurrentState( &Render, &Core, &Input );

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
