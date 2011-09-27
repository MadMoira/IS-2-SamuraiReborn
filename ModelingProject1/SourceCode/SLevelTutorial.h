#pragma once

#include "GameState.h"

#include "Level.h"
#include "MovementPhys.h"
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
    void checkGravity(int vPosition);

private:
	Level *tutorialLevel;
	MovementPhys *movPhysics;
};

