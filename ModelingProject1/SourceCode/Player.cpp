
#include <algorithm>

#include "Player.h"
#include "PlayerState.h"

void Player::stop()
{
  playerSprite->changeStatePlayerSprite(STILL_STATE, 0, this->getInputMapper()->getListKeys());
  getInputMapper()->pushBackStateOnMappedInput(GameCoreStates::STILL);
  playerSprite->changeCurrentFrame(GameCoreStates::STILL);
}

void Player::executeAction()
{
  switch( playerSprite->getCurrentState() )
  {
    case GameCoreStates::STILL:
    {
      noAction();
      break;
    }
	case GameCoreStates::WALKING:
    {
      walk();
      break;
    }
	case GameCoreStates::RUNNING:
	{
      run();
      break;
    }
	case GameCoreStates::JUMPING:
	case GameCoreStates::DOUBLE_JUMP:
    {
      jump();
      break;
	}
  }
}

void Player::drawUIStats()
{
  stats->drawHealthBar();
  stats->drawHealth();
}

void Player::drawScore()
{
  score->drawDisplayPoints();
}

bool Player::isReadyToPace()
{
  if ( playerSprite->getCurrentState() != GameCoreStates::JUMPING && 
	   playerSprite->getCurrentState() != GameCoreStates::DOUBLE_JUMP )
  {
	  return true;
  }

  return false;
}

bool Player::isReadyToDoubleJump()
{
  if ( playerSprite->getSpeedY() >= -8 )
  {
    return true;
  }

  return false;
}

void Player::inputCallback(InputMapping::MappedInput& inputs, Player& player, std::list<InputMapping::Key> keys)
{
  Sprite *playerSprite = player.getPlayerSprite();

  playerSprite->setConstantSpeedX ( 
		        playerSprite->getHandlerAnimation()->changeAnimationDirection(inputs.directionKeyPressed) );

  bool findStillInStates = find(inputs.states.begin(), inputs.states.end(),GameCoreStates::STILL) 
		                   != inputs.states.end();
  bool findWalkingInStates = find(inputs.states.begin(), inputs.states.end(),GameCoreStates::WALKING) 
		                     != inputs.states.end();
  bool findJumpingInStates = find(inputs.states.begin(), inputs.states.end(),GameCoreStates::JUMPING) 
		                     != inputs.states.end();
  bool findRunningInStates = find(inputs.states.begin(), inputs.states.end(),GameCoreStates::RUNNING) 
		                     != inputs.states.end();

  if ( findWalkingInStates && player.isReadyToPace() )
  {
    playerSprite->changeStatePlayerSprite(WALKING_STATE, inputs.buttonPreviouslyPressed, keys);
  }

  if ( findRunningInStates && player.isReadyToPace() )
  {
    playerSprite->changeStatePlayerSprite(RUNNING_STATE, inputs.buttonPreviouslyPressed, keys);
  }

  if ( findJumpingInStates )
  {
    playerSprite->changeStatePlayerSprite(JUMPING_STATE, inputs.jumpKeyPreviouslyPressed, keys);

    if ( player.isReadyToDoubleJump() )
    {
      playerSprite->changeStatePlayerSprite(DOUBLE_JUMP_STATE, inputs.jumpKeyPreviouslyPressed, keys);
    }
  }

  if ( findStillInStates )
  {
    playerSprite->changeStatePlayerSprite(STILL_STATE, inputs.buttonPreviouslyPressed, keys);
  }
}
