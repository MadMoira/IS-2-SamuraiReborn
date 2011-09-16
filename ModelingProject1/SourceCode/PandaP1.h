#pragma once

#include <string>

#include "Player.h"

class PandaP1 : public Player
{
public:
	~PandaP1();

	void initializePlayer(IDSprites id, std::string filename, GLfloat speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
							GLfloat widthSprite, GLfloat heightSprite, int initialFrame, int maxFrame);
	void walk();
	void draw();
	void executeAction();
};