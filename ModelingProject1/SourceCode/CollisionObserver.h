#pragma once

#include "CollisionBox.h"
#include "Enemy.h"
#include "Player.h"

class CollisionObserver
{
public:
	Enemy *enemies;
	Player *players;

	CollisionObserver();
	~CollisionObserver(void);
	//void update();
	bool checkCollision( CollisionBox &A, CollisionBox &B , float direction);
};