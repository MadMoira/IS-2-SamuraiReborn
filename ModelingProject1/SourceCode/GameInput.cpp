
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

bool GameInput::handleKeyStatesPlayers(std::map< int, int > &keyValues, Sprite *playerSprite, Camera *camera)
{
	Uint8 *keystates = SDL_GetKeyState( NULL );
	
	if( keystates[ keyValues[KEY_RIGHT] ] )
    {
		playerSprite->setCurrentState(WALKING);
		playerSprite->setConstantSpeedX ( playerSprite->getHandlerAnimation()->changeAnimationDirection(RIGHT) );
		camera->moveCamera((playerSprite->getSpeedX())/2, (playerSprite->getSpeedY())/2);
		camera->render();
		return true;
	}

	if( keystates[ keyValues[KEY_LEFT] ] )
    {
		playerSprite->setCurrentState(WALKING);
		playerSprite->setConstantSpeedX ( playerSprite->getHandlerAnimation()->changeAnimationDirection(LEFT) );
		camera->moveCamera((playerSprite->getSpeedX())/2, (playerSprite->getSpeedY())/2);
		camera->render();
		return true;
	}
	camera->moveCamera(0, 0);
	playerSprite->setCurrentState(STILL);
	playerSprite->changeCurrentFrame(INITIAL_POSITION);

	return false;
}

