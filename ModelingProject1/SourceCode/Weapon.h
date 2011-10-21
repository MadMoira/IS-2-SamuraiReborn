#pragma once
#include "CollisionBox.h"

class Weapon
{
public:
	Weapon(void);
	~Weapon(void);

private:
	int damage;
	bool actived;
	CollisionBox *weaponCollisionBox;
};

