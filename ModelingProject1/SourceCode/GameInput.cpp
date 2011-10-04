
#include "GameInput.h"

GameInput::GameInput(void)
{
}

GameInput::~GameInput(void)
{
}

bool GameInput::handleWindowEvents(InputMapping::GameInputMapper *gp)
{
	SDL_Event evento;

	while( SDL_PollEvent( &evento ) )
	{
		gp->processNewInput(evento);
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

/*bool GameInput::handleKeyStatesPlayers(std::map< int, int > &keyValues, Sprite *playerSprite)
{
	Uint8 *keystates = SDL_GetKeyState( NULL );
	bool handled=false;
	if(playerSprite->getCurrentState()!=JUMPING){
		if( keystates[ keyValues[KEY_LEFT] ] )
		{
			playerSprite->setConstantSpeedX ( playerSprite->getHandlerAnimation()->changeAnimationDirection(LEFT) );
			playerSprite->setCurrentState(WALKING);

			if( keystates[ keyValues[KEY_RUN] ] )
			{
				playerSprite->setCurrentState(RUNNING);
			}

		
			handled=true;
		}
		else if( keystates[ keyValues[KEY_RIGHT] ] )
		{
			playerSprite->setConstantSpeedX ( playerSprite->getHandlerAnimation()->changeAnimationDirection(RIGHT) );
			playerSprite->setCurrentState(WALKING);

			if( keystates[ keyValues[KEY_RUN] ] )
			{
				playerSprite->setCurrentState(RUNNING);
			}

			handled=true;
		}
		if( keystates[ keyValues[KEY_JUMP] ] )
		{
			playerSprite->setCurrentState(JUMPING);
			handled=true;
		}
		if(handled==false){
			playerSprite->setCurrentState(STILL);
			playerSprite->changeCurrentFrame(STILL);
		}
	}

	else if ( playerSprite->getPosY()+187.0f >= 580.0f )
	{
		if( keystates[ keyValues[KEY_RIGHT] ] )
		{
						playerSprite->setConstantSpeedX ( playerSprite->getHandlerAnimation()->changeAnimationDirection(RIGHT) );
			playerSprite->setCurrentState(WALKING);
					if( keystates[ keyValues[KEY_JUMP] ] )
		{
			playerSprite->setCurrentState(JUMPING);
			handled=true;
		}
		}

		else if ( keystates[ keyValues[KEY_LEFT] ] )
		{
			playerSprite->setConstantSpeedX ( playerSprite->getHandlerAnimation()->changeAnimationDirection(LEFT) );
			playerSprite->setCurrentState(WALKING);
			
			if( keystates[ keyValues[KEY_JUMP] ] )
			{
			playerSprite->setCurrentState(JUMPING);
			handled=true;
			}
		}
		else {
   		playerSprite->setCurrentState(STILL);
		playerSprite->changeCurrentFrame(STILL);}
	}

	return handled;
}*/

