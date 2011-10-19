#pragma once

#include <boost\noncopyable.hpp>

#include "Sprite.h"
#include "Weapon.h"
#include "Stats.h"
#include "PlayerScore.h"
#include "GameInputMapper.h"

#include "Vector.h"

class Player : boost::noncopyable
{
public:

	virtual ~Player() { };

	virtual void initializePlayer(IDSprites id, std::string filename, std::vector< Vector2f > speed, 
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
				std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement) = 0;
	virtual void walk() = 0;
	virtual void run() = 0;
	virtual void jump() = 0;
	virtual void draw() = 0;
	virtual void noAction() = 0;
	virtual void fastAttack() = 0;
	void executeAction();
	void drawUIStats();
	void drawScore();
	void stop();
	void returnToPreviousState();

	static void inputCallback(InputMapping::MappedInput& inputs, Player& player, std::list<InputMapping::Key> keys);

	Sprite* getPlayerSprite() { return playerSprite; }
	bool isReadyToPace();
	bool isReadyToDoubleJump();

	InputMapping::GameInputMapper* getInputMapper() { return inputMapper; }

	PlayerStats::Stats* getPlayerStats() { return stats; }

	Score::PlayerScore* getScore() { return score; }

	void changeFightStyle();
	bool isAlive();

protected:
	Sprite* playerSprite;
	InputMapping::GameInputMapper* inputMapper;
	PlayerStats::Stats* stats;
	Score::PlayerScore* score;
	Weapon* playerWeapon;
};

