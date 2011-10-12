
#include "GameState.h"

GameState::GameState(GameRender *gR, GameCore *gC, GameInput *gI, GameStates stateName)
{
	gameCore = gC;
	gameRender = gR; 
	gameInput = gI;
	nameState = stateName;
}