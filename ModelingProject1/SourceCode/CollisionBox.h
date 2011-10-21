#pragma once

#include "SDL/SDL_image.h"

class CollisionBox{
private:
	SDL_Rect box;

public:
	//Initializes the variables
	CollisionBox();
	CollisionBox(float x, float y ,float w, float h);
	~CollisionBox(void);

	//Takes key presses and adjusts the dot's velocity
	void setx(float n);
	void sety(float n);
	float getx();
	float gety();
	float geth();
	float getw();
};