#pragma once

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"

class GameState
{
public:
	virtual void handleEvents() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~GameState(){};

	int getNameState() { return nameState; }

protected:
	GameState( GameRender *gR, GameCore *gC, GameInput *gI, int stateName );
	GameRender *gameRender;
	GameCore *gameCore;
	GameInput *gameInput;
	int nameState;
};

