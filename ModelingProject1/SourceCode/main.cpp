
#include <windows.h>
#include <gl\GL.h>

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"

#include "GameStateManager.h"

#include "SLevelTutorial.h"

#include "PandaP1.h"

#include "Level.h"

int main( int argc, char* args[] )
{
	GameCore Core;
	GameRender Render;
	GameInput Input;

	GameStateManager StateManager;
	
	if( !Core.initializeGameCore() )
	{
		return 1;
	}

	Core.addPlayerToGame( new PandaP1() );
	
	StateManager.changeState( new SLevelTutorial( &Render, &Core, &Input, STATE_LEVELZEROTUTORIAL ) );
	
	StateManager.render();

	/*Level *levelOne = new Level();
	levelOne->loadTMXTileMapFile("Prueba2.tmx");	

	levelOne->addLayerToList("nubes.png", 1600.f, 720.f, 1.0f, 0.0f);
	levelOne->addLayerToList("mountains.png", 1600.f, 720.f, 3.0f, 0.0f);

	levelOne->drawLevelMap();*/

	while( Core.getIsRunning() )
	{
		Core.getGameTimer()->start();

		StateManager.handleEvents();
		StateManager.logic();
		StateManager.render();

		/*levelOne->scrollBackgroundLayers();
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		    levelOne->drawLevelMap();
		SDL_GL_SwapBuffers();*/

		Core.getGameTimer()->delay();
	}

	//delete levelOne;
	Core.cleanUpGameCore();
	
    return 0;
}
