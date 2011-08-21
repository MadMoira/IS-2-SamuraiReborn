#pragma once

#include "SDL.h"

class GameScreen
{
public:
	GameScreen(void);
	~GameScreen(void);

	void initScreen();
	void updateScreen();

private:
	SDL_Surface *screen;
	int width, height;
};

