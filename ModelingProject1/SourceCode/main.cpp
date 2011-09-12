
#include "GameCore.h"
#include "GameTimer.h"

#include "Level.h"

#include <windows.h>
#include <gl\GL.h>

#define FRAMES_PER_SECOND 15

int main( int argc, char* args[] )
{
	GameCore Core;

	if(Core.initGame() == false)
	{
		return 1;
	}

	Level *levelOne = new Level();
	levelOne->loadTMXTileMapFile("Prueba2.tmx");	

	levelOne->addLayerToList("nubes.png", 1600.f, 720.f, 1.0f, 0.0f);
	levelOne->addLayerToList("mountains.png", 1600.f, 720.f, 3.0f, 0.0f);

	levelOne->drawLevelMap();

	SDL_GL_SwapBuffers();
	
	bool quit = false;
	SDL_Event evento;

	GLfloat offset = 0.f, offset1 = 0.f;
	GameTimer timer;

	while( !quit )
	{
		timer.start();

		while( SDL_PollEvent( &evento ) )
		{
			if( evento.type == SDL_KEYDOWN )
			{
				if(evento.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}
			}
			if(evento.type == SDL_QUIT){
				quit = true;
			}
		}

		levelOne->scrollBackgroundLayers();
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		    levelOne->drawLevelMap();
		SDL_GL_SwapBuffers();

		if( timer.getTicks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - timer.getTicks() );
        }
	}

	delete levelOne;

	SDL_Quit();
	
    return 0;
}
