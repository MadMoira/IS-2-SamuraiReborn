
#include <windows.h>

#include "SDL/SDL_image.h"
#include <GL/GL.h>

#include "GameCore.h"

		
void drawtexture(GLuint texture)
{
        int width, height; 
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
		glBindTexture( GL_TEXTURE_2D, texture );
            glBegin (GL_QUADS);
			glScaled((1280 * width)/width, (720 * height)/height ,0);
				glTexCoord2f (0.0, 0.0);
                glVertex3f (0.0, 0.0, 0.0);
                glTexCoord2f (1.0, 0.0);
                glVertex3f (width, 0.0, 0.0);
                glTexCoord2f (1.0, 1.0);
                glVertex3f (width, height, 0.0);
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
	
	GLuint texe1 = Core.loadTexture("imagen.png");
	GLuint texe2 = Core.loadTexture("y.png");
	drawtexture(texe1);
	drawtexture(texe2);
	
	bool quit = false;
	SDL_Event evento;
	float temp = 0;

	while(quit == false)
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

		SDL_GL_SwapBuffers();
	
	}
	
	return 0;
}
