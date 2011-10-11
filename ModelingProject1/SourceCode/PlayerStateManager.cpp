
#include "PlayerStateManager.h"
#include "PlayerState.h"

PlayerStateManager::PlayerStateManager(void)
{
  currentState = *STILL_STATE;
}

PlayerStateManager::~PlayerStateManager(void)
{
  statesStack.clear();
}

void PlayerStateManager::pushState(GameCoreStates::PlayerState* playerState)
{
  statesStack.push_back(playerState);
}

void PlayerStateManager::popState()
{
  statesStack.pop_back();
}

void PlayerStateManager::changeState(GameCoreStates::PlayerState* newState)
{
  previousState = GameCoreStates::SpriteState(currentState.getCurrentID());

  while( !statesStack.empty() )
  {
    popState();
  }

  pushState(newState);
  currentState = *newState;
}
