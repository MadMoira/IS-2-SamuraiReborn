#pragma once

#include "Player.h"

class MeerkatP2 : public Player
{
public:
	~MeerkatP2();

	void initializePlayer(IDSprites id, std::string filename, GLfloat speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
								GLfloat widthSprite, GLfloat heightSprite, int initialFrame, int maxFrame);
	void walk() {};
	void draw() {};
	void executeAction() {};
	
};

