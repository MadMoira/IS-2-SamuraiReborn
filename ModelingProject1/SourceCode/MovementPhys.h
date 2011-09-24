#pragma once

#include <windows.h>
#include <math.h>
#include <GL/gl.h>

enum physicState{
	PARABOLIC,
	PERRA
};

class MovementPhys
{

public:
	void physicManager(GLfloat *xVelocity, GLfloat *yVelocity, int state); 
	MovementPhys(float gravityVal);
	~MovementPhys(void);
	
	
private:
	float gravityVal;
	void parabolicShot(GLfloat *yVelocity);

};

