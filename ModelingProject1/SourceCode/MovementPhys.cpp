#include "MovementPhys.h"


MovementPhys::MovementPhys(int gravityVal)
{
	this->gravityVal = gravityVal;
	
}

MovementPhys::~MovementPhys(void)
{
}

void MovementPhys::parabolicShot(GLfloat *yVelocity){
	*yVelocity -= this->gravityVal ;

}

void MovementPhys::physicManager(GLfloat *xVelocity, GLfloat *yVelocity, physicState state){
	switch(state)
	{
	case PROYECTIL:
		parabolicShot(yVelocity);
		break;
	}
}
