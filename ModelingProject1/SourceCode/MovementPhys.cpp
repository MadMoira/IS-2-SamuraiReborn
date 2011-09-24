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

void MovementPhys::physicManager(GLfloat *xVelocity, GLfloat *yVelocity, int state){
	switch(state)
	{
	case PARABOLIC:
		parabolicShot(yVelocity);
		break;
	}
}
