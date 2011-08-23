#pragma once

#include "Sprite.h"
#include "Weapon.h"
#include "Stats.h"

class Player
{
public:
	Player(void);

	~Player(void);

	/*virtual void attack();
	virtual void block();
	virtual void executeAction();
	virtual void handleInput();
	virtual void jump();
	virtual void walk();*/

	void changeFightStyle();
	void getPlayerStats();
	bool isAlive();

private:
	int currentFightMode;
	int currentHealth, currentStamina;
	Sprite *playerSprite;
	Stats *stats;
	Weapon *playerWeapon;
};

