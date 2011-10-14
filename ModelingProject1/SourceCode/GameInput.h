#pragma once

#include "SDL/SDL.h"
#include <map>
#include <string>

#include "Sprite.h"
#include "GameInputMapper.h"

#include "Camera.h"

class GameInput
{
public:
	GameInput(void);
	~GameInput(void);

	bool handleWindowEvents();
	void handleKeyEvents(InputMapping::GameInputMapper* gameInputMapper);
};

