#pragma once

#include "Sprite.h"
#include "Weapon.h"

class Enemy
{
public:
	Sprite *getSprite() { return enemySprite; }

	virtual void initializeEnemy(IDSprites id, std::string filename, std::vector< Vector2f> speed,
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
				std::vector< Vector2f> delayMovement) = 0;
	virtual void walk() = 0;
	virtual void run() = 0;
	virtual void jump() = 0;
	virtual void draw() = 0;
	virtual void noAction() = 0;
	virtual void attack() = 0;
	void executeAction();
	void stop();
	void returnToPreviousState();

	bool isReadyToPace();
	bool isReadyToDoubleJump();

	Sprite* getEnemySprite() { return enemySprite; }

	~Enemy(void){};

protected:
	Sprite *enemySprite;
	Weapon *enemyWeapon;
	int health;
	int modeIA;
	int pointsForDeath;
};

