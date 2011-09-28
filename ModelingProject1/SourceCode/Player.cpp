
#include "Player.h"

void Player::executeAction()
{
	switch( playerSprite->getCurrentState() )
	{
	case STILL:
		{
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
	}
}