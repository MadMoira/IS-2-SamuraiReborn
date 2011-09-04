#include "GameCore.h"

#include "Level.h"

#include <windows.h>
#include <gl\GL.h>

int main( int argc, char* args[] )
{
	GameCore Core;

	if(Core.initGame() == false)
	{
		return 1;
	}

	Level *levelOne = new Level();
	levelOne->loadTMXTileMapFile("test1.tmx");	
	
	levelOne->drawLevelMap();

	GLuint texture1 = Core.loadTexture("Mov1.png");
	GLuint texture2 = Core.loadTexture("InitialPosition.png");
    
	Core.drawTexture(texture1, 0.0f, 0.0f, 800.0f, 600.0f);

	glTranslatef(100.0f, 30.0f, 0.0f);

	Core.drawTexture(texture2, 0.0f, 0.0f, 800.0f, 600.0f);

	SDL_GL_SwapBuffers();
	
	bool quit = false;
	SDL_Event evento;

	while( !quit )
	{
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
	}

	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	delete levelOne;

	SDL_Quit();
	
    return 0;
}
