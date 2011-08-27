#pragma once

#include "SDL.h"
#include "SDL_opengl.h"
#include <string>

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
	std::string windowName;
};

