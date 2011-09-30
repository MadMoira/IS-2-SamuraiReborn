
#include "GameInput.h"

GameInput::GameInput(void)
{
}

GameInput::~GameInput(void)
{
}

bool GameInput::handleWindowEvents()
{
	SDL_Event evento;

	while( SDL_PollEvent( &evento ) )
	{
		if( evento.type == SDL_KEYDOWN )
		{
			if( evento.key.keysym.sym == SDLK_ESCAPE )
			{
				return false;
			}
		}
		
		if( evento.type == SDL_QUIT)
		{
			return false;
		}
	}
	
	return true;
}

bool GameInput::handleKeyStatesPlayers(std::map< int, int > &keyValues, Sprite *playerSprite)
{
	Uint8 *keystates = SDL_GetKeyState( NULL );
	
	if( keystates[ keyValues[KEY_RIGHT] ] )
    {
		playerSprite->setCurrentState(WALKING);

		if( keystates[ keyValues[KEY_RUN] ] )
		{
			playerSprite->setCurrentState(RUNNING);
		}

		playerSprite->setConstantSpeedX ( playerSprite->getHandlerAnimation()->changeAnimationDirection(RIGHT) );
		return true;
	}

	if( keystates[ keyValues[KEY_LEFT] ] )
    {
		playerSprite->setCurrentState(WALKING);

		if( keystates[ keyValues[KEY_RUN] ] )
		{
			playerSprite->setCurrentState(RUNNING);
		}

		playerSprite->setConstantSpeedX ( playerSprite->getHandlerAnimation()->changeAnimationDirection(LEFT) );
		return true;
	}
	playerSprite->setCurrentState(STILL);
	playerSprite->changeCurrentFrame(STILL);

	return false;
}

