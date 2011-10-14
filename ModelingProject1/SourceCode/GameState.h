#pragma once

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"

enum GameStates 
{
	STATE_NULL,
	STATE_INTRO, 
	STATE_MAINMENU, 
	STATE_LEVELZEROTUTORIAL, 
	STATE_EXIT,
};

class GameState
{
public:
	virtual void init() = 0;
	virtual void handleEvents() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~GameState(){};

	GameStates getNameState() { return nameState; }

protected:
	GameState( GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName );
	GameRender* gameRender;
	GameCore* gameCore;
	GameInput* gameInput;
	GameStates nameState;
};

