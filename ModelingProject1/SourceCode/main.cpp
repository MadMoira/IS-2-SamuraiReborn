#include <windows.h>
#include <gl\GL.h>
#include "CollisionObserver.h"
#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"
#include "GameStateManager.h"
#include "SLevelTutorial.h"
#include "PandaP1.h"
#include "Level.h"

int main( int argc, char* args[] ){

	GameCore Core;
	GameRender Render;
	GameInput Input;
	GameStateManager StateManager;
	CollisionObserver observer = CollisionObserver();
	
	if( !Core.initializeGameCore() )
		return 1;
	
	//Core.addPlayerToGame( new PandaP1() );

	StateManager.changeState( new SLevelTutorial( &Render, &Core, &Input, STATE_LEVELZEROTUTORIAL ) );
	//motion rate
	float x=0.0f;
	float dx;
	//collision boxes
	CollisionBox box1= CollisionBox(x+80, 100 , 180,  498);
	CollisionBox box2= CollisionBox(250+246, 100 , 462,  537);
	
	//Images
	GLuint texture1 = Core.loadTexture("Mov1.png");

	GLuint texture2 = Core.loadTexture("InitialPosition.png");

	GLuint textureBackground = Core.loadTexture("background.jpg");

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
		bool quit = false;
	    SDL_Event evento;
				if(evento.key.keysym.sym == SDLK_RIGHT){
					dx = 20.0f;
					x+=dx;
					box1.setx(x+80);
					if(observer.checkCollision(box1,box2,dx)==true){
						x-=dx;
					}
					box1.setx(x+80);
				}
				if(evento.key.keysym.sym == SDLK_LEFT){
					dx = -20.0f;
					x+=dx;
					box1.setx(x+80);
					if(observer.checkCollision(box1,box2,dx)==true){
						x-=dx;
					}
					box1.setx(x+80);
				}
				if(evento.key.keysym.sym == SDLK_1){
					x=1000.0;
				}
				if(evento.key.keysym.sym == SDLK_2){
					x=0.0;
				}

		Render.drawFullTexture(textureBackground, 0.0f, 0.0f, 1280.0f, 720.0f);

		Render.drawFullTexture(texture1, x, 100.0f, 800.0f, 600.0f);

		Render.drawFullTexture(texture2, 250.0f, 100.0f, 800.0f, 600.0f);

		SDL_GL_SwapBuffers();
	}

	//delete levelOne;
	Core.cleanUpGameCore();

	return 0;
}