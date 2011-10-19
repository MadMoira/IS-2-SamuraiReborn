#include "MovementPhys.h"


MovementPhys::MovementPhys(float gravityVal)
{
  this->gravityVal = gravityVal;
  countY = 0;
  delayY = 5;
}

MovementPhys::~MovementPhys(void)
{
}

void MovementPhys::parabolicShot(GLfloat* yVelocity)
{
  countY++;
  if( countY > delayY )
  {
    countY = 0;
    *yVelocity -= this->gravityVal ;
  }
}

void MovementPhys::physicManager(Vector2f* speed, int state)
{
  switch(state)
  {
   case PARABOLIC:
   {
    parabolicShot(&speed->y);
    break;
   }
  }
}
