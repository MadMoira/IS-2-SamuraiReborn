#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "GameState.h"

enum GameStates 
{
	STATE_NULL,
	STATE_INTRO, 
	STATE_MAINMENU, 
	STATE_LEVELZEROTUTORIAL, 
	STATE_EXIT,
};

class GameStateManager
{
public:
	GameStateManager(void);
	~GameStateManager(void);
	
	void pushState( GameState *gameState );
	void popState();
	void changeState( GameState *gameState ) ;

	void handleEvents();
	void logic();
	void render();

protected:
	boost::ptr_vector< GameState > statesStack;
	int currentState, currentID;
};

