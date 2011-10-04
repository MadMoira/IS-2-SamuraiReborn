#pragma once

#include "SDL/SDL.h"
#include <map>
#include <string>

#include "Sprite.h"
#include "GameInputMapper.h"

class GameInput
{
public:
	GameInput(void);
	~GameInput(void);

	bool handleWindowEvents(InputMapping::GameInputMapper *gp);
	bool handleKeyStatesPlayers(std::map< int, int > &keyValues, Sprite *playerSprite);
};

