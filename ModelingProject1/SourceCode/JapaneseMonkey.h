#pragma once

#include "Enemy.h"

class JapaneseMonkey : public Enemy
{
public:
	void initializeEnemy(IDSprites id, std::string filename, std::vector< Vector2f > speed, 
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite);
	void walk();
	void run();
	void jump();
	void draw();
	void noAction();
	void executeAction();
	void attack();
	~JapaneseMonkey();
};

