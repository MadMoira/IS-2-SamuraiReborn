#include "GameScreen.h"


GameScreen::GameScreen(void)
{
	screen = NULL;
	width = 800;
	height = 600;
}

bool GameScreen::initialize()
{

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    if( SDL_SetVideoMode( width, height, 32, SDL_OPENGL ) == NULL ) //32 BPP
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
	glViewport(0,0,1280,720);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, 1280, 720, 0, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glAlphaFunc(GL_GREATER,0.1f);
	//glEnable(GL_ALPHA_TEST);
	glClearColor(1.0f,1.0f,1.0f,1.0f);

    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    return true;
}

GameScreen::~GameScreen(void)
{
}
