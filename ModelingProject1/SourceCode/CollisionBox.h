#pragma once

#include "SDL/SDL_image.h"

class CollisionBox
{
  public:
   CollisionBox();
   CollisionBox(float x, float y ,float w, float h);
   ~CollisionBox(void);

   float getX() { return box.x; }
   void setX(float x, int i) { 
	   if ( i == 0 ) {
		   box.x = (Sint16)x + 42; }
	   else
   {
	   box.x = x; }
   }

   float getY() { return box.y; }
   void setY(float y) { box.y = (Sint16)y + 45; }

   float getHeight() { return box.h; }
   float getWidth() { return box.w; }

  private:
   SDL_Rect box;
};