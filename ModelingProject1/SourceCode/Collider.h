#pragma once

#include <boost/ptr_container/ptr_vector.hpp>
#include "CollisionBox.h"
#include "Enemy.h"
#include "Player.h"

class Collider
{
public:
	
	Collider::Collider();
	Collider::Collider(boost::ptr_vector< Enemy > *enemies, boost::ptr_vector< Player > *players);
	~Collider(void);
	
	bool checkCollision( CollisionBox &A, CollisionBox &B , float direction);
	bool checkTileCollision( Sprite &A, float directionX);
	bool checkEnemiesCollision( CollisionBox &A, float directionX);
	boost::ptr_vector< Player > Collider::checkEnemiesAttackCollision( CollisionBox &A, float directionX);
	boost::ptr_vector< Enemy > checkAttackCollision( CollisionBox &A, float directionX);
	bool onTheGround(Sprite &A, float directionX);
	
private:
	boost::ptr_vector< Enemy > *enemies;
	boost::ptr_vector< Player > *players;
};