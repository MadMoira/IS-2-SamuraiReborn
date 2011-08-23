#pragma once

#include <windows.h>

#include <GL/gl.h>

enum IDSprites 
{ 
	PANDA, 
	MEERKAT, 
	JAPANESEMONKEY 
};

class Sprite
{
public:
	Sprite(void);
	~Sprite(void);

	void draw();

private:
	GLuint texture;
	int ID, width, height;
	float posX, posY;
	float speedX, speedY, countX, countY;
	float delayX, delayY;
	int frameCount, frameDelay, animationDirection;
	int currentFrame, currentState, maxFrameFromCurrentState;
};

