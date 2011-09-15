#include "GameScreen.h"
#include <iostream>

using namespace std;

GameScreen::GameScreen(void)
{
	screen = NULL;
	width = height = 0;
	windowName = "Unnamed 2D Game";
}

GameScreen::~GameScreen(void)
{
}

bool GameScreen::initializeScreen()
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        return false;
    }
	
	if( SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ) != 0)
	{
		return false;
	}

	width = 1280;	height = 720;

	if( (screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL ) ) == NULL) 
    {
        return false;
    }

    if( initializeOpenGL() == false )
    {
        return false;
    }

	SDL_WM_SetCaption( windowName.c_str(), NULL );

    return true;
}

bool GameScreen::initializeOpenGL()
{	
	defaultResolution = SDL_GetVideoInfo();
	float proportion = ((float)defaultResolution->current_w / (float)defaultResolution->current_h);
	
	glViewport(0, 0, defaultResolution->current_w, defaultResolution->current_h);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
		
	if(proportion > 1.5 && proportion < 1.7)
	{
		glOrtho( 0, 1280,800, 0, -1, 1 );
	}

	else if(proportion > 1.7 && proportion < 1.8)
	{
		glOrtho( 0, 1280,720, 0, -1, 1 );
	}

	else
	{
		glOrtho( 0, 1280,960, 0, -1, 1 );
	}
	
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    return true;
}


