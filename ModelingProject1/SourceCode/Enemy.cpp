#include "Enemy.h"


Enemy::Enemy()
{
	//enemySprite = new Sprite();
	enemyWeapon = new Weapon();
}


Enemy::~Enemy(void)
{
	//delete enemySprite;
	delete enemyWeapon;
}