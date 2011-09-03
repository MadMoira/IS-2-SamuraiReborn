#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

class GameScreen
{
public:
	GameScreen(void);
	~GameScreen(void);

	void initScreen();
	void updateScreen();
	bool initializeOGL();
	bool initialize();

private:
	SDL_Surface *screen;
	int width, height;
};

