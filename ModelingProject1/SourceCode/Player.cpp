
#include "Player.h"
#include <fstream>

void Player::stop()
{
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

void Player::inputCallback(InputMapping::MappedInput& inputs, Player& player)
{
	std::fstream file;
	file.open("logKeys.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	
	bool bcurrentState = inputs.states.find(InputMapping::WALKING) != inputs.states.end();
	if ( bcurrentState == true && player.getPlayerSprite()->getCurrentState() != JUMPING )
	{
		player.getPlayerSprite()->setCurrentState( WALKING );}

	if ( bcurrentState == true && player.getPlayerSprite()->getCurrentState() == JUMPING 
		&& player.getPlayerSprite()->getPreviousState() == WALKING && inputs.actions.find(InputMapping::JUMPING) != inputs.actions.end() )
	{
		player.getPlayerSprite()->setCurrentState( DOUBLE_JUMP );
		
	}

	if ( bcurrentState == false && player.getPlayerSprite()->getCurrentState() == JUMPING )
	{
		player.getPlayerSprite()->setCurrentState( JUMPING );
		if ( player.getPlayerSprite()->getSpeedY() >= -8 && 
			inputs.actions.find(InputMapping::JUMPING) != inputs.actions.end() && player.getPlayerSprite()->getPreviousState() != DOUBLE_JUMP )
		{
			player.getPlayerSprite()->setCurrentState( DOUBLE_JUMP );
		}

	}
	
	if ( bcurrentState == false && player.getPlayerSprite()->getCurrentState() != JUMPING )
	{
		player.getPlayerSprite()->setCurrentState( STILL );
	}

	if(inputs.actions.find(InputMapping::JUMPING) != inputs.actions.end())
	{
		player.getPlayerSprite()->setCurrentState( JUMPING );
	}

	file.close();
}