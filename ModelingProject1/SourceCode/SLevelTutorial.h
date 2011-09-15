#pragma once

#include "GameState.h"

class SLevelTutorial : public GameState
{
public:
	SLevelTutorial( GameRender *gR, GameCore *gC, GameInput *gI, int stateName );
	~SLevelTutorial();

	void handleEvents();
	void logic();
	void render();
};

