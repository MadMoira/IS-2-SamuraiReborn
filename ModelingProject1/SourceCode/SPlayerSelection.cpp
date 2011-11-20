#include "SPlayerSelection.h"


SPlayerSelection::SPlayerSelection(GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName) 
	: GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;
  setHasEnded(STATE_MAINMENU);
}

SPlayerSelection::~SPlayerSelection(void)
{
}

void SPlayerSelection::init()
{
}

void SPlayerSelection::handleEvents()
{
}

void SPlayerSelection::logic()
{
}

void SPlayerSelection::render()
{
}

void SPlayerSelection::cleanUp()
{
}