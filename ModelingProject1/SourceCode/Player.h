#pragma once

#include <boost\noncopyable.hpp>

#include "Sprite.h"
#include "Weapon.h"
#include "Stats.h"
#include "KeyboardHandler.h"

class Player : boost::noncopyable
{
public:

	virtual ~Player() { };
	
	/*virtual void attack();
	virtual void block();
	virtual void executeAction();
	virtual void jump();
	
	*/
	virtual void initializePlayer(IDSprites id, std::string filename, GLfloat speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
								GLfloat widthSprite, GLfloat heightSprite, int initialFrame, int maxFrame) = 0;
	virtual void walk() = 0;
	virtual void draw() = 0;
	virtual void executeAction() = 0;

	Sprite *getPlayerSprite() { return playerSprite; }

	KeyboardHandler *getKeyboardHandler() { return keyboardHandler; }

	void changeFightStyle();
	void getPlayerStats();
	bool isAlive();

protected:
	int currentFightMode;
	int currentHealth, currentStamina;
	Sprite *playerSprite;
	Stats *stats;
	Weapon *playerWeapon;
	KeyboardHandler *keyboardHandler;
};

