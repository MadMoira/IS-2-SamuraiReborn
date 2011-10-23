#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>

#include "GameRender.h"

#include "Animation.h"
#include "PlayerStateManager.h"

#include "Vector.h"

enum IDSprites 
{ 
	PANDA, 
	MEERKAT, 
	JAPANESEMONKEY, 
};

class Sprite
{
public:
	Sprite(IDSprites id, std::string filename, std::vector< Vector2f > speed, Vector2f pos, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
				GLfloat widthSprite, GLfloat heightSprite);
	~Sprite(void);

	GLfloat getPosX() { return position.x; }
	bool movePosXWithSpeed();
	GLfloat getPosY() { return position.y; }
	bool movePosYWithSpeed();

	GLfloat getSpeedX() { return currentXSpeed; }
	GLfloat getStateXSpeed() { return speed.at(getCurrentState()).x; }
	GLfloat getPreviousStateXSpeed() { return speed.at(getPreviousState()).x; }

	void setSpeedX(GLfloat speedX);
	void setConstantSpeedX(int constant);

	GLfloat getSpeedY() { return currentYSpeed; }
	void setSpeedY(GLfloat newSpeedY){currentYSpeed=newSpeedY;}

	GLfloat getDelayX() { return delay.x; }
	void setDelayX(GLfloat newDelay){delay.x=newDelay;}

	GLfloat getDelayY() { return delay.y; }

	GLuint getTexture() { return texture; }

	GLfloat getWidthTexture(){ return width;}

	Animation *getHandlerAnimation() { return handlerAnimation; }
	void changeCurrentFrame(int frame);

	int getCurrentState() { return playerStateManager->getCurrentState(); }

	void changeStatePlayerSprite(GameCoreStates::PlayerState* newState, int keyPreviouslyPressed, 
		                         std::list<InputMapping::Key> keys);

	void changeStateEnemySprite(GameCoreStates::PlayerState* newState);

	int getPreviousState() { return playerStateManager->getPreviousState(); }

	void drawTexture();

private:
	IDSprites ID;
	GLuint texture;
	Animation* handlerAnimation;
	GameCoreStates::PlayerStateManager* playerStateManager;
	Vector2f position, delay;
	std::vector< Vector2f > speed;
	std::vector< int > maxFramesPerAnimation;
	std::vector< int > returnFramesPerAnimation;
	GLfloat width, height, widthTexture, heightTexture;
	GLfloat currentXSpeed, currentYSpeed;
	GLfloat countX, countY;
	int frameCount, frameDelay;
};

