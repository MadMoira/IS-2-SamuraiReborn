#pragma once

#include "GameState.h"

#include "Level.h"
#include "MovementPhys.h"

class SLevelTutorial : public GameState
{
public:
	SLevelTutorial( GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName );
	~SLevelTutorial();

	void init();
	void handleEvents();
	void logic();
	void render();
    void checkGravity(int vPosition);

private:
	Level* tutorialLevel;
	MovementPhys* movPhysics;
};

