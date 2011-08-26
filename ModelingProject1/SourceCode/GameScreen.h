#pragma once

#include "SDL.h"
#include "SDL_opengl.h"

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

