#pragma once

#include "GameState.h"

#include "Level.h"

#include "PandaP1.h"
#include "MeerkatP2.h"

class SLevelTutorial : public GameState
{
public:
	SLevelTutorial( GameRender *gR, GameCore *gC, GameInput *gI, GameStates stateName );
	~SLevelTutorial();

	void init();
	void handleEvents();
	void logic();
	void render();
	void camera();

private:
	Level *tutorialLevel;
};

