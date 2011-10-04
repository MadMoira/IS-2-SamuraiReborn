#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>

#include "GameRender.h"

#include "Animation.h"

#include "Vector.h"

enum IDSprites 
{ 
	PANDA, 
	MEERKAT, 
	JAPANESEMONKEY, 
};

enum IDSpriteStates
{
	STILL,
	WALKING,
	JUMPING,
	RUNNING,
	DOUBLE_JUMP,
};

class Sprite
{
public:
	Sprite(IDSprites id, std::string filename, std::vector< Vector2f > speed, GLfloat speedY, Vector2f pos, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, IDSpriteStates state,
				GLfloat widthSprite, GLfloat heightSprite);
	~Sprite(void);

	GLfloat getPosX() { return position.x; }
	bool movePosXWithSpeed();
	GLfloat getPosY() { return position.y; }
	bool movePosYWithSpeed();

	GLfloat getSpeedX() { return currentXSpeed; }
	GLfloat getStateXSpeed() { return speed.at(currentState).x; }
	GLfloat getPreviousStateXSpeed() { return speed.at(previousState).x; }

	void setSpeedX(GLfloat speedX) { currentXSpeed = speedX; }
	void setConstantSpeedX(int constant);

	GLfloat getSpeedY() { return speedY; }
	void setSpeedY(GLfloat newSpeedY){speedY=newSpeedY;}

	GLfloat getDelayX() { return delay.x; }

	GLfloat getDelayY() { return delay.y; }

	GLuint getTexture() { return texture; }

	Animation *getHandlerAnimation() { return handlerAnimation; }
	void changeCurrentFrame(int frame);

	int getCurrentState() { return currentState; }
	void setCurrentState(IDSpriteStates state);

	int getPreviousState() { return previousState; }

	void drawTexture();

private:
	IDSprites ID;
	GLuint texture;
	Animation *handlerAnimation;
	int currentState, previousState;
	Vector2f position, delay;
	std::vector< Vector2f > speed;
	std::vector< int > maxFramesPerAnimation;
	std::vector< int > returnFramesPerAnimation;
	GLfloat width, height, widthTexture, heightTexture;
	GLfloat currentXSpeed;
	GLfloat speedY, countX, countY;
	int frameCount, frameDelay;
};

