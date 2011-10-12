#pragma once

#include "SDL.h"
#include "SDL_opengl.h"
#include <string>

class GameScreen
{
public:
	GameScreen(void);
	~GameScreen(void);

	bool initializeScreen();
	bool initializeOpenGL();
	bool initializeSDLGLState();
	
private:
	SDL_Surface *screen;
	int width, height;
	std::string windowName;
	const SDL_VideoInfo* defaultResolution;
};

