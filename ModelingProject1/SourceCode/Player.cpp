
#include "Player.h"

void Player::stop(){
	playerSprite->setCurrentState(STILL);
	playerSprite->changeCurrentFrame(STILL);
}

void Player::executeAction()
{
	switch( playerSprite->getCurrentState() )
	{
	case STILL:
		{
			noAction();
			break;
		}
	case WALKING:
		{
			walk();
			break;
		}
	case RUNNING:
		{
			run();
			break;
		}
	case JUMPING:
		{
			jump();
			break;
		}
	}
}