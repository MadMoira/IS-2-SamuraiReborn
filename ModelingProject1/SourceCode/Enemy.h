#pragma once

#include "Sprite.h"
#include "Weapon.h"

class Enemy
{
public:
	Enemy(void);
	~Enemy(void);

private:
	Sprite *enemySprite;
	Weapon *enemyWeapon;
	int health;
	int modeIA;
	int pointsForDeath;
};

