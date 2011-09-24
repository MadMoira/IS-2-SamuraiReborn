#pragma once

#include <math.h>
//#include <GL/gl.h>

enum physicState{
	PROYECTIL,
	FREEFALLING
};

class MovementPhys
{

public:
	void physicManager(float *xVelocity, float *yVelocity, physicState estate); 
	MovementPhys(int gravityVal);
	~MovementPhys(void);
	
	
private:
	int gravityVal;
	void ParabolicShot(int *xVelocity,int *yVelocity);

};

