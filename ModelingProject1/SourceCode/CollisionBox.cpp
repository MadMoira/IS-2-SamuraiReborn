#include "CollisionBox.h"

CollisionBox::CollisionBox(float x, float y ,float w, float h)
{
  box.x= (Sint16)x;
  box.y= (Sint16)y;
  box.w = (Sint16)w;
  box.h = (Sint16)h;
}

CollisionBox::~CollisionBox(void)
{
}