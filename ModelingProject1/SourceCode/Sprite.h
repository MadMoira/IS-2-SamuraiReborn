#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>
#include "GameRender.h"
#include "CollisionBox.h"
#include "Animation.h"
class Collider;

enum IDSprites 
{ 
	PANDA, 
	MEERKAT, 
	JAPANESEMONKEY 
};

enum IDSpriteStates
{
	STILL,
	WALKING,
	JUMPING,
	RUNNING
};

class Sprite
{
public:
	Sprite(IDSprites id, std::string filename, std::vector<GLfloat> speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, IDSpriteStates state,
				GLfloat widthSprite, GLfloat heightSprite);
	~Sprite(void);

	GLfloat getPosX() { return posX; }
	bool movePosXWithSpeed();

	GLfloat getPosY() { return posY; }
	GLfloat getWidth() { return width; }
	GLfloat getHeight() { return height; }

	GLfloat getSpeedX() { return speedXVector.at(currentState); }
	void setSpeedX(GLfloat speedX) { speedXVector.at(currentState) = speedX; }
	void setConstantSpeedX(int constant);

	GLfloat getSpeedY() { return speedY; }

	GLfloat getDelayX() { return delayX; }

	GLfloat getDelayY() { return delayY; }

	GLuint getTexture() { return texture; }

	CollisionBox *getCollisionBox(){return spriteCollisionBox; }

	Animation *getHandlerAnimation() { return handlerAnimation; }
	void changeCurrentFrame(int frame);

	int getCurrentState() { return currentState; }
	void setCurrentState(IDSpriteStates state);

	void drawTexture();

private:
	IDSprites ID;
	GLuint texture;
	Animation *handlerAnimation;
	IDSpriteStates currentState;
	std::vector< int > maxFramesPerAnimation;
	std::vector< int > returnFramesPerAnimation;
	GLfloat width, height, widthTexture, heightTexture;
	GLfloat posX, posY;
	std::vector< GLfloat > speedXVector;
	GLfloat speedY, countX, countY;
	GLfloat delayX, delayY;
	int frameCount, frameDelay;
	CollisionBox *spriteCollisionBox;
	Collider *cHandler;
};

