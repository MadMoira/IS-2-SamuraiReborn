

#include <crtdbg.h>

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"
#include "PhysicsCore.h"

#include "GameStateManager.h"

#include "SIntro.h"
#include "SMainMenu.h"
#include "SLevelOneJapan.h"

//#include <vld.h>

int main( int argc, char* args[] )
{
	int bgX = 0, bgY = 0;
  GameCore Core;
  GameRender Render;
  GameInput Input;
  GamePhysics::PhysicsCore* Physics;
  GameStateManager *StateManager = new GameStateManager();
	
  if( !Core.initializeGameCore() )
  {
    return 1;
  }

  Physics = GamePhysics::PhysicsCore::getInstance();
  Physics->initializePhysicValues(-4.0f);

  //StateManager->changeState( new SMainMenu( &Render, &Core, &Input, Physics, STATE_MAINMENU ) );
  StateManager->changeState( new SLevelOneJapan( &Render, &Core, &Input, Physics, STATE_LEVELONEJAPAN ) );
  StateManager->init();


  while( Core.getIsRunning() )
  {
    StateManager->changeCurrentState( &Render, &Core, &Input, Physics );

    Core.getGameTimer()->start();

    StateManager->handleEvents();
    StateManager->logic();
    StateManager->render();

    Core.getGameTimer()->delay();
  }
  
  StateManager->cleanUp();

  delete StateManager;

  Core.cleanUpGameCore();

	Core.cleanUpGameCore();
	_CrtDumpMemoryLeaks();
  return 0;
}
