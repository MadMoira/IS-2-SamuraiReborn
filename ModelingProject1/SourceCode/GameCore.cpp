#include "GameCore.h"

#include "SDL/SDL_image.h"

GameCore::GameCore()
{
	currentGameState = 0;
	configuration = new GameConfiguration();
	saves = new GameSaves();
	screen = new GameScreen();
	timer = new GameTimer();
	currentStateID = STATE_NULL;
}

bool GameCore::initGame()
{
	if( screen->initialize() )
	{
		return true;
	}
	return false;
}

GameCore::~GameCore(void)
{
	delete currentGameState;
	delete configuration;
	delete saves;
	delete screen;
	delete timer;
}

SDL_Surface *GameCore::load_image( std::string filename )
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

GLuint GameCore::loadTexture(std::string name)
{
	SDL_Surface* image = load_image(name);
	
	GLuint texture;

	if( image != NULL )
	{
		glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(	GL_TEXTURE_2D,
						0, 
						4, 
						image->w, 
						image->h,
						0, 
						GL_BGRA,
						GL_UNSIGNED_BYTE, 
						image->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		SDL_FreeSurface(image);
		return texture;
	}

	return NULL;
}
