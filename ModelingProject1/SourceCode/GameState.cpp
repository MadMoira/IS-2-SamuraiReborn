
#include "GameState.h"

GameState::GameState(GameRender *gR, GameCore *gC, GameInput *gI, GamePhysics::PhysicsCore* gP, 
	                                                              GameStates stateName)
{
	gameCore = gC;
	gameRender = gR; 
	gameInput = gI;
	gamePhysics = gP;
	nameState = stateName;
}