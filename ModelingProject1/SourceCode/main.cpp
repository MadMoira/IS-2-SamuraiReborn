#include "GameCore.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
using namespace std;

SDL_Surface *load_image( string filename )
{
    SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

void loadTexture(string name){
	
	SDL_Surface* background = load_image(name);
	const SDL_VideoInfo* resolution = SDL_GetVideoInfo();
	GLuint texture;

	if(background!=NULL){
		
		glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(	GL_TEXTURE_2D,
						0, 
						4, 
						background->w, 
						background->h,
						0, 
						GL_BGRA,
						GL_UNSIGNED_BYTE, 
						background->pixels);

		

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBegin (GL_QUADS);
		glScaled((1280 * background->w)/background->w,
	    	     (720 * background->h)/background->h
				 ,0);
		glTexCoord2f (0.0, 0.0);
		glVertex3f (0.0, 0.0, 0.0);
		glTexCoord2f (1.0, 0.0);
		glVertex3f (background->w, 0.0, 0.0);
		glTexCoord2f (1.0, 1.0);
		glVertex3f (background->w, background->h, 0.0);
		glTexCoord2f (0.0, 1.0);
		glVertex3f (0.0, background->h, 0.0);
		glEnd ();
		SDL_FreeSurface(background);
	}
}

int main( int argc, char* args[] )
{
	GameCore core;
	
	if(core.initGame()==false){
		return 1;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	loadTexture("imagen.png");
	loadTexture("x.png");
	loadTexture("y.png");

	SDL_GL_SwapBuffers();
	
	bool quit = false;
	SDL_Event evento;

	float temp = 0;
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
