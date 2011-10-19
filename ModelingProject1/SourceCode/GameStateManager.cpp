
#include "GameStateManager.h"

#include "SLevelTutorial.h"

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

void GameStateManager::changeCurrentState(GameRender* gR, GameCore* gC, GameInput* gI)
{
  int newChangeState = checkIfCurrentStateHasEnd();

  if ( newChangeState != statesStack.at(0).getNameState() )
  {
    switch(newChangeState)
	{
	  case STATE_LEVELZEROTUTORIAL:
	  {
        changeState(new SLevelTutorial( gR, gC, gI, STATE_LEVELZEROTUTORIAL ) );
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

int GameStateManager::checkIfCurrentStateHasEnd()
{
  return statesStack.at(0).checkIfStateEnd();
}