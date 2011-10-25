
#include "GameStateManager.h"

#include "SIntro.h"
#include "SMainMenu.h"
#include "SLevelOneJapan.h"

GameStateManager::GameStateManager(void)
{
  currentState = STATE_NULL;
  currentID = 0;
}

GameStateManager::~GameStateManager(void)
{
  statesStack.clear();
}

void GameStateManager::pushState(GameState *gameState)
{
  statesStack.push_back(gameState);
}

void GameStateManager::popState()
{
  statesStack.pop_back();
}

void GameStateManager::changeState(GameState *gameState)
{
  while( !statesStack.empty() )
  {
    popState();
  }

  pushState(gameState);
  currentState = gameState->getNameState();
}

void GameStateManager::changeCurrentState(GameRender* gR, GameCore* gC, GameInput* gI, GamePhysics::PhysicsCore* gP)
{
  int newChangeState = checkIfCurrentStateHasEnd();

  if ( newChangeState != statesStack.at(0).getNameState() )
  {
    switch(newChangeState)
	{
	  case STATE_INTRO:
	  {
		cleanUp();
        changeState(new SIntro( gR, gC, gI, gP, STATE_INTRO ) );
        break;
      }

	  case STATE_MAINMENU:
	  {
		cleanUp();
        changeState(new SMainMenu( gR, gC, gI, gP, STATE_MAINMENU ) );
        break;
      }
	  
	  case STATE_LEVELONEJAPAN:
	  {
		cleanUp();
        changeState(new SLevelOneJapan( gR, gC, gI, gP, STATE_LEVELONEJAPAN ) );
        break;
      }
	}

	init();
  }
}

void GameStateManager::init()
{
  statesStack.at(currentID).init();
}

void GameStateManager::handleEvents()
{
  statesStack.at(currentID).handleEvents();
}

void GameStateManager::logic()
{
  statesStack.at(currentID).logic();
}

void GameStateManager::render()
{
  statesStack.at(currentID).render();
}

void GameStateManager::cleanUp()
{
  statesStack.at(currentID).cleanUp();
}

int GameStateManager::checkIfCurrentStateHasEnd()
{
  return statesStack.at(0).checkIfStateEnd();
}