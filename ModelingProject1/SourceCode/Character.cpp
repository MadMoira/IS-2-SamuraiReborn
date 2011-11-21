
#include "Character.h"

void Characters::Character::initializeSpriteCollisionBox(float width, float height, GLfloat offsetX, GLfloat offsetY)
{
  characterSprite->initializeSpriteCollisionBox(width, height, offsetX, offsetY);
}

bool Characters::Character::isStoppingMovement(std::list<InputMapping::Key> keys)
{
  GameCoreStates::ConditionsPlayerRunning inputDirection = 
                  characterSprite->getPlayerStateManager()->getObjectState().checkIfPlayerIsRunning(keys);

  if ( !inputDirection.directionButtonPressed && !inputDirection.runningButtonPressed )
  {
    return true;
  }

  return false;
}

bool Characters::Character::isReadyToPace()
{
  if ( characterSprite->getCurrentState() != GameCoreStates::JUMPING &&
       characterSprite->getCurrentState() != GameCoreStates::DOUBLE_JUMP && 
       characterSprite->getCurrentState() != GameCoreStates::FALLING )
  {
    return true;
  }

  return false;
}

bool Characters::Character::isReadyToDoubleJump()
{
  if ( characterSprite->getSpeedY() >= -8 && characterSprite->getSpeedY() <= 0  )
  {
    return true;
  }

  return false;
}

bool Characters::Character::isFalling()
{
  if ( characterSprite->getIsOnGround() )
  {
    return false;
  }

  if ( characterSprite->getSpeedY() >= 0)
  {
    return true;
  }

  return false;
}

bool Characters::Character::isAlive()
{
  if ( characterSprite->getBoxY() > 720.0f )
  {
    return false;
  }

  return true;
}