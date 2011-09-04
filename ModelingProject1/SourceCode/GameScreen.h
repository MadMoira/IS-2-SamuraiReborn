#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
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
	int width, heigth;
	std::string windowName;
	const SDL_VideoInfo* defaultResolution;
};

