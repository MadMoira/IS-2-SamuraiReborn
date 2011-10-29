
#include "CollisionStructs.h"

void CollisionSystem::CharacterMovement::setMoveX(bool moveX)
{
  playerMoveInX = moveX;
}

void CollisionSystem::CharacterMovement::setMoveY(bool moveY)
{
  playerMoveInY = moveY;
}

void CollisionSystem::CharacterMovement::setMoveXFrame(bool moveX)
{
  playerMoveInXInCurrentFrame = moveX;
}

void CollisionSystem::CharacterMovement::setMoveYFrame(bool moveY)
{
  playerMoveInYInCurrentFrame = moveY;
}