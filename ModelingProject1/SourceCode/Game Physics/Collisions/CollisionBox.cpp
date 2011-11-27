#include "CollisionBox.h"
#include "SpriteDataConstants.h"

CollisionSystem::CollisionBox::CollisionBox(float x, float y ,float w, float h, Vector2f offset)
{
  box.x= (Sint16)x;
  box.y= (Sint16)y;
  box.w = (Sint16)w;
  box.h = (Sint16)h;
  offsetBox = offset;
}

CollisionSystem::CollisionBox::~CollisionBox(void)
{
}

void CollisionSystem::CollisionBox::setX(float x, int direction)
{
  if ( direction == SpriteData::RIGHT )
  {
    box.x = (Sint16)x + (Sint16)offsetBox.x;
    return;
  }

  box.x = (Sint16)x;
}

void CollisionSystem::CollisionBox::setY(float y)
{
  box.y = (Sint16)y + (Sint16)offsetBox.y;
}

float CollisionSystem::CollisionBox::getOffsetXPosition(int direction)
{
  if ( direction == SpriteData::RIGHT )
  {
    return box.w;
  }

  return 0.0f;
}

float CollisionSystem::CollisionBox::getOffsetXBasedOnDirection(int direction)
{
  if ( direction == SpriteData::RIGHT )
  {
    return offsetBox.x;
  }

  return 0.0f;
}