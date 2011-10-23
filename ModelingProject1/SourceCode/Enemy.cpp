#include "Enemy.h"


void Enemy::stop()
{
  enemySprite->changeStateEnemySprite(STILL_STATE);
  enemySprite->changeCurrentFrame(GameCoreStates::STILL);
}

void Enemy::returnToPreviousState()
{
  switch( enemySprite->getPreviousState() )
  {
    case GameCoreStates::WALKING:
    {
	  enemySprite->changeStateEnemySprite(WALKING_STATE);
    }
  }
  enemySprite->changeCurrentFrame( enemySprite->getCurrentState() ); 
}

void Enemy::executeAction()
{
  switch( enemySprite->getCurrentState() )
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
	case GameCoreStates::FAST_ATTACK_WALKING:
	{
	  attack();
	  break;
	}
  }
}


bool Enemy::isReadyToPace()
{
  if ( enemySprite->getCurrentState() != GameCoreStates::JUMPING && 
	   enemySprite->getCurrentState() != GameCoreStates::DOUBLE_JUMP )
  {
	  return true;
  }

  return false;
}

bool Enemy::isReadyToDoubleJump()
{
  if ( enemySprite->getSpeedY() >= -8 )
  {
    return true;
  }

  return false;
}
