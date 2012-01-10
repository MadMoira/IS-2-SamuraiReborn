
#include "GameStateManager.h"

#include "SIntro.h"
#include "SMainMenu.h"
#include "SLevelOneJapan.h"
#include "SPlayerSelection.h"
#include "SPause.h"

GameStateManager::GameStateManager(void)
{
  currentState = MainStates::STATE_NULL;
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

void GameStateManager::changeState(GameState* gameState)
{
  while( !statesStack.empty() )
  {
    popState();
  }

  pushState(gameState);
  currentState = gameState->getNameState();
  currentID = 0;
}

void GameStateManager::changeCurrentState(GameRender* gR, GameCore* gC, GameInput* gI)
{
  using namespace MainStates;

  int newChangeState = checkIfCurrentStateHasEnd();
  int currentGameState = statesStack.at(currentID).getNameState();
  if ( newChangeState != currentGameState && ( currentGameState != STATE_PAUSE ||
	   newChangeState == STATE_MAINMENU ) )
  {
    switch(newChangeState)
    {
      case STATE_INTRO:
      {
        cleanUp();
        changeState(new SIntro( gR, gC, gI, STATE_INTRO ) );
        break;
      }
      case STATE_MAINMENU:
      {
        cleanUp();
        changeState(new SMainMenu( gR, gC, gI, STATE_MAINMENU ) );
        break;
      }
      case STATE_MENUSELECTIONPLAYER:
      {
        cleanUp();
        changeState(new SPlayerSelection( gR, gC, gI, STATE_MENUSELECTIONPLAYER ) );
        break;
      }
      case STATE_LEVELONEJAPAN:
      {
        cleanUp();
        changeState(new SLevelOneJapan( gR, gC, gI, STATE_LEVELONEJAPAN ) );
        break;
      }
	  case STATE_PAUSE:
	  {
		statesStack.push_back(new SPause( gR, gC, gI, STATE_PAUSE) );
		currentID = 1;
		currentState = statesStack.at(currentID).getNameState();
		break;
	  }
    }

	init();
	return;
  }

  if ( newChangeState != statesStack.at(currentID).getNameState() )
  {
    if ( statesStack.at(currentID).getNameState() == STATE_PAUSE  )
    {
      statesStack.pop_back();
	  currentState = statesStack.at(0).getNameState();
	  currentID = 0;
	  resume();
    }
  }
}

void GameStateManager::init()
{
  statesStack.at(currentID).init();
}

void GameStateManager::resume()
{
  statesStack.at(currentID).resume();
}

void GameStateManager::startTimer()
{
  statesStack.at(currentID).getGameTimer().start();
}

void GameStateManager::delayTimer()
{
  statesStack.at(currentID).getGameTimer().delay();
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
  return statesStack.at(currentID).checkIfStateEnd();
}