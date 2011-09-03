#include "GameCore.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
using namespace std;


void drawtexture(GLuint){
	int widht, height; 
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &widht);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	glBegin (GL_QUADS);
	glTexCoord2f (0.0, 0.0);
	glVertex3f (0.0, 0.0, 0.0);
	glTexCoord2f (1.0, 0.0);
	glVertex3f (widht, 0.0, 0.0);
	glTexCoord2f (1.0, 1.0);
	glVertex3f (widht, height, 0.0);
	glTexCoord2f (0.0, 1.0);
	glVertex3f (0.0, height, 0.0);
	glEnd ();
}

int main( int argc, char* args[] )
{
	GameCore core;

	if(core.initGame()==false){
		return 1;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,0.0f);
	GLuint texe1 = core.loadTexture("imagen.png");
	GLuint texe2 = core.loadTexture("x.png");
	GLuint texe3 = core.loadTexture("y.png");
    glBindTexture(GL_TEXTURE_2D, texe1);
	drawtexture(texe1);
	glBindTexture(GL_TEXTURE_2D, texe2);
	drawtexture(texe2);
	glBindTexture(GL_TEXTURE_2D, texe3);
	drawtexture(texe3);

	SDL_GL_SwapBuffers();
	
	bool quit = false;
	SDL_Event evento;

	bool adelante=true;
	while(quit==false){
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
	
    return 0;
}
