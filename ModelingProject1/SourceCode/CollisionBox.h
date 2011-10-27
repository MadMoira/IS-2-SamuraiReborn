#pragma once

#include "SDL/SDL_image.h"

class CollisionBox
{
  public:
   CollisionBox();
   CollisionBox(float x, float y ,float w, float h);
   ~CollisionBox(void);

   float getX() { return box.x; }
   void setX(float x) { box.x = (Sint16)x + 42; }

   float getY() { return box.y; }
   void setY(float y) { box.y = (Sint16)y + 45; }

   float getHeight() { return box.h; }
   float getWidth() { return box.w; }

  private:
   SDL_Rect box;
};