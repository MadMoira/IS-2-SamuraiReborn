#include "GameCore.h"

#include "Level.h"

#include <windows.h>
#include <gl\GL.h>


void drawtexture(GLuint)
{
	int width, height; 

	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

	glBegin (GL_QUADS);
		glTexCoord2f (0.0, 0.0);
		glVertex3f (0.0, 0.0, 0.0);
		glTexCoord2f (1.0, 0.0);
		glVertex3f ( (GLfloat)width, 0.0, 0.0);
		glTexCoord2f (1.0, 1.0);
		glVertex3f ( (GLfloat)width, (GLfloat)height, 0.0);
		glTexCoord2f (0.0, 1.0);
		glVertex3f (0.0, (GLfloat)height, 0.0);
	glEnd ();
}

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

	GLuint texe1 = Core.loadTexture("Mov1.png");
	GLuint texe2 = Core.loadTexture("InitialPosition.png");

    glBindTexture(GL_TEXTURE_2D, texe1);
	drawtexture(texe1);

	glTranslatef(100.0f, 30.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texe2);
	drawtexture(texe2);

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

	delete levelOne;

	SDL_Quit();
	
    return 0;
}
