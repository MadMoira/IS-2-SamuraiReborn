#include "Player.h"


Player::Player(void)
{
	playerSprite = new Sprite();
	stats = new Stats();
	playerWeapon = 0;
}


Player::~Player(void)
{
	delete playerWeapon;
	delete stats;
	delete playerSprite;
}
