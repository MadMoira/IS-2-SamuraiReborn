#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <GL/gl.h>

#include "GameRender.h"

#include "Animation.h"
#include "PlayerStateManager.h"

#include "CollisionBox.h"
#include "CollisionStructs.h"

#include "Vector.h"

class Collider;

enum IDSprites 
{ 
  PANDA, 
  MEERKAT, 
};

class Sprite
{
  public:
   Sprite(IDSprites id, std::string filename, std::vector< Vector2f > speed, Vector2f pos, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
				GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
				std::vector< Vector2f> delayMovement);
   ~Sprite(void);

   GLfloat getPosX() { return position.x; }
   void movePosXWithSpeed();
   GLfloat getPosY() { return position.y; }
   void movePosYWithSpeed();

   CollisionSystem::CharacterMovement getCharacterMovement() { return characterMovement; }

	bool getPlayerMoveInX() { return characterMovement.playerMoveInX; }
	void setPlayerMoveInX(bool moveX) { characterMovement.setMoveX(moveX); }

	bool getPlayerMoveInY() { return characterMovement.playerMoveInY; }
	void setPlayerMoveInY(bool moveY) { characterMovement.setMoveY(moveY); }

	GLfloat getSpeedX() { return currentXSpeed; }
	GLfloat getStateXSpeed() { return speed.at(getCurrentState()).x; }
	GLfloat getPreviousStateXSpeed() { return speed.at(getPreviousState()).x; }

	void setSpeedX(GLfloat speedX);
	void setConstantSpeedX(int constant);

	void restartCountX() { countX = 0; }

	GLfloat getSpeedY() { return currentYSpeed; }
	void setSpeedY(GLfloat speedY);

	GLuint getTexture() { return texture; }

	GLfloat getWidthTexture(){ return widthTexture;}

	GLfloat getWidth() { return width; }

	GLfloat getHeight() { return height; }

	Animation *getHandlerAnimation() { return handlerAnimation; }
	void changeCurrentFrame(int frame);

	int getCurrentState() { return playerStateManager->getCurrentState(); }

	void changeStatePlayerSprite(GameCoreStates::PlayerState* newState, int keyPreviouslyPressed, 
		                         std::list<InputMapping::Key> keys);

	void changeStateEnemySprite(GameCoreStates::PlayerState* newState);

	int getPreviousState() { return playerStateManager->getPreviousState(); }

	GLfloat getCurrentDelayFromCurrentState() { return delayMovementSprite.at(getCurrentState()).x; }
	int getCountX() { return countX; }

	Collider* getCollisionHandler() { return collisionHandler; }

	CollisionBox* getCollisionBox() {return spriteCollisionBox; }

	GLfloat getBoxX() { return spriteCollisionBox->getX(); }
	GLfloat getBoxY() { return spriteCollisionBox->getY(); }
	GLfloat getBoxWidth() { return spriteCollisionBox->getWidth(); }
	GLfloat getBoxHeight() { return spriteCollisionBox->getHeight(); }

	bool getPlayerMoveInXCurrentFrame() { return characterMovement.playerMoveInXInCurrentFrame; }
	bool getPlayerMoveInYCurrentFrame() { return characterMovement.playerMoveInYInCurrentFrame; }

	void drawTexture();
	bool canMove;

private:
	IDSprites ID;
	GLuint texture;
	Animation* handlerAnimation;
	GameCoreStates::PlayerStateManager* playerStateManager;
	CollisionBox* spriteCollisionBox;
	Collider* collisionHandler;
	CollisionSystem::DirectionsMove directionsMove;
	CollisionSystem::CharacterMovement characterMovement;
	Vector2f position;
	std::vector< Vector2f > speed;
	std::vector< Vector2f > delayMovementSprite;
	std::vector< int > maxFramesPerAnimation;
	std::vector< int > returnFramesPerAnimation;
	std::vector< int > frameratePerAnimation;
	GLfloat width, height, widthTexture, heightTexture;
	GLfloat currentXSpeed, currentYSpeed;
	int countX, countY;
	bool onG;
};

