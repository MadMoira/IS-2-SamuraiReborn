#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "GameState.h"

class GameStateManager
{
public:
	GameStateManager(void);
	~GameStateManager(void);
	
	void pushState( GameState* gameState );
	void popState();
	void changeState( GameState* gameState ) ;
	void changeCurrentState(GameRender* gR, GameCore* gC, GameInput* gI, GamePhysics::PhysicsCore* gP);

	void init();
	void handleEvents();
	void logic();
	void render();
	void cleanUp();

private:
	boost::ptr_vector< GameState > statesStack;
	GameStates currentState;
	int currentID;

    int checkIfCurrentStateHasEnd();
};

