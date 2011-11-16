
#include "PlayerStateManager.h"
#include "PlayerState.h"

GameCoreStates::PlayerStateManager::PlayerStateManager(void)
{
  currentState = *STILL_STATE;
}

GameCoreStates::PlayerStateManager::~PlayerStateManager(void)
{
  statesStack.clear();
}

void GameCoreStates::PlayerStateManager::pushState(GameCoreStates::PlayerState* playerState)
{
  statesStack.push_back(playerState);
}

void GameCoreStates::PlayerStateManager::popState()
{
  statesStack.pop_back();
}

void GameCoreStates::PlayerStateManager::changeState(GameCoreStates::PlayerState* newState)
{
  previousState = GameCoreStates::SpriteState(currentState.getCurrentID());
  if(previousState == GameCoreStates::RUNNING){
	  GameSound::getInstance()->closeSound();
  }
  /*if(previousState == GameCoreStates::FALLING){
	  GameSound::getInstance()->loadChunk("groundHit.mp3");
  }*/
  if(previousState == GameCoreStates::JUMPING/* && newState->getCurrentID() != GameCoreStates::FALLING*/){
	  GameSound::getInstance()->loadChunk("groundHit.mp3");
  }
  
  while( !statesStack.empty() )
  {
    popState();
  }

  pushState(newState);
  currentState = *newState;
}

void GameCoreStates::PlayerStateManager::changePreviousState(GameCoreStates::SpriteState previousID)
{
  previousState = GameCoreStates::SpriteState(previousID);
}
