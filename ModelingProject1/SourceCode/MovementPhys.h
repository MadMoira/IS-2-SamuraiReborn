#pragma once

#include <windows.h>
#include <math.h>
#include <GL/gl.h>

#include "Vector.h"

enum physicState
{
	PARABOLIC
};

class MovementPhys
{

public:
	MovementPhys(float gravityVal);
	~MovementPhys(void);
	
	void physicManager(Vector2f* speed, int state);

private:
	float gravityVal;
	void parabolicShot(GLfloat* speedY);
	int countY, delayY;
};

