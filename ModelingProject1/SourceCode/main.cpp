#include "GameScreen.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
using namespace std;

SDL_Surface *load_image( std::string filename )
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
				
		SDL_FreeSurface(background);

		glBegin (GL_QUADS);
		glTexCoord2f (0.0, 0.0);
		glVertex3f (0.0, 0.0, 0.0);
		glTexCoord2f (1.0, 0.0);
		glVertex3f (800, 0.0, 0.0);
		glTexCoord2f (1.0, 1.0);
		glVertex3f (800, 600, 0.0);
		glTexCoord2f (0.0, 1.0);
		glVertex3f (0.0, 600, 0.0);
		glEnd ();
	}
	
}

int main( int argc, char* args[] )
{
	GameScreen screen;
	if(screen.initialize()==false){
		return 1;
	}
	loadTexture("x.png");
	
	loadTexture("y.png");

	SDL_GL_SwapBuffers();
	
	bool quit = false;
	SDL_Event evento;

	float temp = 0;
	bool adelante=true;
	while(quit==false){
		while( SDL_PollEvent( &evento ) )
		{
			if(adelante){
				temp++;			
			}
			else{
				temp--;			
			}
			if(temp<0){adelante=false;}
			else if(temp>100){adelante=true;}
			glTranslatef(temp,0.0f,0.0f);
			loadTexture("x.png");
	
			loadTexture("y.png");

			SDL_GL_SwapBuffers();
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
