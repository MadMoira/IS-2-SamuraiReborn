#pragma once

#include "SDL/SDL.h"
#include <map>
#include <string>

#include "Sprite.h"
#include "KeyboardHandler.h"

#include "Camera.h"

class GameInput
{
public:
	GameInput(void);
	~GameInput(void);

	bool handleWindowEvents();
	bool handleKeyStatesPlayers(std::map< int, int > &keyValues, Sprite *playerSprite, Camera* camera);
};

