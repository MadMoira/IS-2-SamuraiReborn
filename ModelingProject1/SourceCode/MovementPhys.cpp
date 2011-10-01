#include "MovementPhys.h"


MovementPhys::MovementPhys(float gravityVal)
{
	this->gravityVal = gravityVal;
	
}

MovementPhys::~MovementPhys(void)
{
}

void MovementPhys::parabolicShot(GLfloat *yVelocity){
	*yVelocity -= this->gravityVal ;

}

void MovementPhys::physicManager(Vector2f *speed, int state)
{
	switch(state)
	{
	case PARABOLIC:
		parabolicShot(&speed->y);
		break;
	}
}
