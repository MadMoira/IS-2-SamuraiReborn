#pragma once

#include <windows.h>
#include <math.h>
#include <GL/gl.h>

enum physicState{
	PROYECTIL
};

class MovementPhys
{

public:
	void physicManager(GLfloat *xVelocity, GLfloat *yVelocity, physicState estate); 
	MovementPhys(int gravityVal);
	~MovementPhys(void);
	
	
private:
	int gravityVal;
	void parabolicShot(GLfloat *yVelocity);

};

