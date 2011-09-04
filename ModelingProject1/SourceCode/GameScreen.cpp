#include "GameScreen.h"
#include <iostream>

using namespace std;

GameScreen::GameScreen(void)
{
	screen = NULL;
	width = 0;
	height = 0;
	
}

bool GameScreen::initialize()
{
	
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }
	
	if(SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ) != 0)
	{
		return false;
	}

	if( SDL_SetVideoMode( width, height, 32, SDL_OPENGL ) == NULL ) 
    {
        return false;
    }

    if( initializeOGL() == false )
    {
        return false;
    }

	SDL_WM_SetCaption( "Unnamed Game!", NULL );

    return true;
}

bool GameScreen::initializeOGL()
{	
	const SDL_VideoInfo* resolution = SDL_GetVideoInfo();
	float proportion = ((float)resolution->current_w / (float)resolution->current_h);
	
	glViewport(0, 0, resolution->current_w, resolution->current_h);
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    return true;
}

GameScreen::~GameScreen(void)
{
}
