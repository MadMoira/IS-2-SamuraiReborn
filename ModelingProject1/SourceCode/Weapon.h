#pragma once

#include "CollisionBox.h"

class Weapon
{
public:
	Weapon(void);
	~Weapon(void);
	int getDamage();

private:
	int damage;
	bool actived;
	CollisionSystem::CollisionBox* weaponCollisionBox;
};

