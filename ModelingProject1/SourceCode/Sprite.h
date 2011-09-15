#pragma once

#include <windows.h>
#include <string>
#include <GL/gl.h>

#include "GameRender.h"

#define INITIAL_POSITION 0

enum IDSprites 
{ 
	PANDA, 
	MEERKAT, 
	JAPANESEMONKEY 
};

enum IDSpriteStates
{
	STILL,
	WALKING
};

class Sprite
{
public:
	Sprite(IDSprites id, std::string filename, GLfloat speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
			int initialFrame, int maxFrame, GLfloat widthSprite, GLfloat heightSprite);
	~Sprite(void);

	GLfloat getPosX() { return posX; }
	bool movePosXWithSpeed();

	GLfloat getPosY() { return posY; }

	GLfloat getSpeedX() { return speedX; }

	GLfloat getSpeedY() { return speedY; }

	GLfloat getDelayX() { return delayX; }

	GLfloat getDelayY() { return delayY; }

	GLuint getTexture() { return texture; }

	int getCurrentFrame() { return currentFrame; }
	void setCurrentFrame(int frame) { currentFrame = frame; }

	int getCurrentState() { return currentState; }
	void setCurrentState(int state);

	void updateCurrentSpriteFrame();

	void drawTexture();

private:
	GLuint texture;
	int ID;
	GLfloat width, height, widthTexture, heightTexture;
	GLfloat posX, posY;
	GLfloat speedX, speedY, countX, countY;
	GLfloat delayX, delayY;
	int frameCount, frameDelay, animationDirection;
	int currentFrame, currentState, maxFrameFromCurrentState;
};

