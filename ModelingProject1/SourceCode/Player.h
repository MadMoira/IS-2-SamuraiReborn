#pragma once

#include <boost\noncopyable.hpp>

#include "Sprite.h"
#include "Weapon.h"
#include "Stats.h"
#include "GameInputMapper.h"
#include "MovementPhys.h"

#include "Vector.h"

class Player : boost::noncopyable
{
public:

	virtual ~Player() { };
	
	/*virtual void attack();
	virtual void block();	
	*/

	virtual void initializePlayer(IDSprites id, std::string filename, std::vector< Vector2f > speed, GLfloat speedY, 
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, IDSpriteStates state, GLfloat widthSprite, GLfloat heightSprite) = 0;
	virtual void walk() = 0;
	virtual void run() = 0;
	virtual void jump() = 0;
	virtual void draw() = 0;
	virtual void noAction() = 0;
	void executeAction();

	static void inputCallback(InputMapping::MappedInput& inputs, Player& player);

	void stop(); 
	Sprite *getPlayerSprite() { return playerSprite; }

	InputMapping::GameInputMapper *getInputMapper() { return inputMapper; }

	void changeFightStyle();
	void getPlayerStats();
	bool isAlive();

protected:
	int currentFightMode;
	int currentHealth, currentStamina;
	Sprite *playerSprite;
	InputMapping::GameInputMapper *inputMapper;
	Stats *stats;
	Weapon *playerWeapon;
};

