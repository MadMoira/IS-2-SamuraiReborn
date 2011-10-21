#pragma once

#include "Sprite.h"
#include "Weapon.h"

class Enemy
{
public:
	Enemy::Enemy();
	~Enemy(void);
	Sprite *getSprite() { return enemySprite; }

private:
	Sprite *enemySprite;
	Weapon *enemyWeapon;
	int health;
	int modeIA;
	int pointsForDeath;
};

