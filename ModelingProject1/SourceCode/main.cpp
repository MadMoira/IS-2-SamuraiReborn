#include "GameCore.h"

#include <windows.h>

#include <GL/GL.h>

#include "SDL/SDL_image.h"


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
	GameCore Core;

	if( Core.initGame() == false)
	{
		return 1;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f,10.0f,0.0f);

	GLuint texe1 = Core.loadTexture("imagen.png");
	GLuint texe2 = Core.loadTexture("x.png");
	GLuint texe3 = Core.loadTexture("y.png");
	drawtexture(texe1);
	drawtexture(texe2);
	drawtexture(texe3);
	
	bool quit = false;
	SDL_Event evento;
	float temp = 0;
	bool adelante=true;

	while(quit == false){
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
		SDL_GL_SwapBuffers();
	}
	
	return 0;
}
