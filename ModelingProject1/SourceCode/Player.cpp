
#include <algorithm>
#include "ComparatorFunctions.h"

#include "Player.h"

#include "Collider.h"

void Player::initializeSpriteCollisionBox(float width, float height, GLfloat offsetX, GLfloat offsetY)
{
  playerSprite->initializeSpriteCollisionBox(width, height, offsetX, offsetY);
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
	case GameCoreStates::FAST_ATTACK:
	{
	  fastAttack();
	  break;
	}
	case GameCoreStates::FALLING:
    {
      falling();
      break;
    }
	case GameCoreStates::STOPPING:
    {
      stopping();
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

void Player::stop()
{
  if ( !playerSprite->getPlayerMoveInX() && !playerSprite->getPlayerMoveInY() )
  {
    playerSprite->changeStatePlayerSprite(STILL_STATE, 0, getInputMapper()->getListKeys());
    getInputMapper()->pushBackStateOnMappedInput(GameCoreStates::STILL);
    playerSprite->changeCurrentFrame(GameCoreStates::STILL);
  }
}

bool Player::isStoppingMovement(std::list<InputMapping::Key> keys)
{
  GameCoreStates::ConditionsPlayerRunning inputDirection = 
	              playerSprite->getPlayerStateManager()->getObjectState().checkIfPlayerIsRunning(keys);

  if ( !inputDirection.directionButtonPressed && !inputDirection.runningButtonPressed )
  {
    return true;
  }

  return false;
}

void Player::returnToPreviousState()
{
  switch( playerSprite->getPreviousState() )
  {
    case GameCoreStates::STILL:
    {
	  playerSprite->changeStatePlayerSprite(STILL_STATE, 0, getInputMapper()->getListKeys());
	  break;
    }
    case GameCoreStates::WALKING:
    {
	  playerSprite->changeStatePlayerSprite(WALKING_STATE, 1, getInputMapper()->getListKeys());
	  break;
    }
	case GameCoreStates::RUNNING:
    {
      playerSprite->changeStatePlayerSprite(RUNNING_STATE(playerSprite->getID()), 1, getInputMapper()->getListKeys());
	  break;
    }
	case GameCoreStates::JUMPING:
    {
	  playerSprite->changeStatePlayerSprite(FALLING_STATE, 0, getInputMapper()->getListKeys());
	  break;
    }
  }

  getInputMapper()->pushBackStateOnMappedInput( GameCoreStates::SpriteState( playerSprite->getCurrentState() ) );
  playerSprite->changeCurrentFrame( playerSprite->getCurrentState() ); 
}

bool Player::isReadyToPace()
{
  if ( playerSprite->getCurrentState() != GameCoreStates::JUMPING &&
	   playerSprite->getCurrentState() != GameCoreStates::DOUBLE_JUMP && 
	   playerSprite->getCurrentState() != GameCoreStates::FALLING )
  {
    return true;
  }

  return false;
}

bool Player::isReadyToDoubleJump()
{
  if ( playerSprite->getSpeedY() >= -8 && playerSprite->getSpeedY() <= 0  )
  {
    return true;
  }

  return false;
}

bool Player::isFalling()
{
  if ( playerSprite->getIsOnGround() )
  {
	return false;
  }

  if ( playerSprite->getSpeedY() >= 0)
  {
    return true;
  }

  return false;
}

bool Player::isAlive()
{
  if ( playerSprite->getBoxY() > 720.0f )
  {
    return false;
  }

  return true;
}

void Player::inputCallback(InputMapping::MappedInput& inputs, Player& player, std::list<InputMapping::Key> keys)
{
  Sprite* playerSprite = player.getPlayerSprite();

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
  bool findFastAttackWalkingInStates = find(inputs.states.begin(), inputs.states.end(), 
	                                   GameCoreStates::FAST_ATTACK) != inputs.states.end();

  InputMapping::Key checkKey = *std::find_if(keys.begin(), keys.end(), isJumpingKeyPressed);

  if ( findWalkingInStates && player.isReadyToPace() )
  {
    playerSprite->changeStatePlayerSprite(WALKING_STATE, inputs.buttonPreviouslyPressed, keys);
  }

  if ( findRunningInStates && player.isReadyToPace() )
  {
    playerSprite->changeStatePlayerSprite(RUNNING_STATE(playerSprite->getID()), inputs.buttonPreviouslyPressed, keys);
  }
  if ( findJumpingInStates )
  {
    playerSprite->changeStatePlayerSprite(JUMPING_STATE(playerSprite->getID()), checkKey.wasPreviouslyPressed, keys);

    if ( player.isReadyToDoubleJump() )
    {
      playerSprite->changeStatePlayerSprite(DOUBLE_JUMP_STATE, checkKey.wasPreviouslyPressed, keys);
    }

    if ( player.isFalling() )
    {
      playerSprite->changeStatePlayerSprite(FALLING_STATE, checkKey.wasPreviouslyPressed, keys);
    }
  }

  if ( player.isStoppingMovement(keys) )
  {
	playerSprite->changeStatePlayerSprite(STOPPING_STATE, inputs.buttonPreviouslyPressed, keys);
  }

  if ( findStillInStates )
  {
    playerSprite->changeStatePlayerSprite(STILL_STATE, inputs.buttonPreviouslyPressed, keys);
  }

  if ( findFastAttackWalkingInStates )
  {
    checkKey = *std::find_if(keys.begin(), keys.end(), isFastAttackKeyPressed);
    playerSprite->changeStatePlayerSprite(FAST_ATTACK_STATE(playerSprite->getID()), checkKey.wasPreviouslyPressed, keys);
  }
}
