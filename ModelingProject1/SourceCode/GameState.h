#pragma once

#include "GameCore.h"
#include "GameRender.h"
#include "GameInput.h"
#include "PhysicsCore.h"

enum GameStates 
{
  STATE_NULL,
  STATE_INTRO, 
  STATE_MAINMENU, 
  STATE_LEVELZEROTUTORIAL, 
  STATE_LEVELONEJAPAN,
  STATE_EXIT,
};

class GameState
{
public:
	virtual void init() = 0;
	virtual void handleEvents() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual void cleanUp() = 0;
	virtual ~GameState(){};

	GameStates getNameState() { return nameState; }

	int checkIfStateEnd() { return hasEnded; }
	void setHasEnded(int stateHasEnded) { hasEnded = stateHasEnded; }

private:
	int hasEnded;

protected:
	GameState( GameRender* gR, GameCore* gC, GameInput* gI, GamePhysics::PhysicsCore* gP, GameStates stateName );
	GameRender* gameRender;
	GameCore* gameCore;
	GameInput* gameInput;
	GamePhysics::PhysicsCore* gamePhysics;
	GameStates nameState;
    std::vector< std::string > sounds;	
	
};

