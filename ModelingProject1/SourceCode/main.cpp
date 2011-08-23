/*This source code copyrighted by Lazy Foo' Productions (2004-2011)
and may not be redestributed without written permission.*/

//The headers

#include <windows.h>

#include "SDL.h"
#include "SDL_image.h"
#include <string>

#include "Level.h"

#include <GL/gl.h>

int main( int argc, char* args[] )
{
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Surface *gameMainSurface;
	//const SDL_VideoInfo* myPointer = SDL_GetVideoInfo(); //Return a struct with information about the actual video mode

	int width = 1280; //Width and height for testing
	int height = 720;

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); //Establish a mode about how OpenGL it's going to work
	gameMainSurface = SDL_SetVideoMode( width, height, 32, SDL_OPENGL) ; //Create the surface for the game 

	//----------------------------------------------
	//----Initialize OpenGL for 2D------------------

	glEnable( GL_TEXTURE_2D );
 
	glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );

	glViewport( 0, 0, width, height );
	 
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	 
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	 
	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	 
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	//----------------------------------------------
	//----------------------------------------------

	Level *levelOne = new Level();
	levelOne->loadTMXTileMapFile("example.tmx");

	SDL_Quit();

	return 0;
}
