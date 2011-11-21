
#include "EnemySprite.h"

EnemySprite::EnemySprite(SpriteData::IDSprites id, std::string filename, std::vector< Vector2f > speed, Vector2f pos, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
				GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
				std::vector< Vector2f> delayMovement) : Sprite(id, filename, speed, pos, initialFrame, maxFrame,
				                                               returnFrame, widthSprite, heightSprite, framerateAnimations,
															   delayMovement)
{
}

void EnemySprite::changeStateSprite(GameCoreStates::PlayerState* newState, int keyPreviouslyPressed, 
		                            std::list<InputMapping::Key> keys)
{
  int resultCheckingEqualStates = newState->checkIfEqualStates(keys, getCurrentState(),
		                          getPreviousState(), newState, keyPreviouslyPressed);

  if ( resultCheckingEqualStates == GameCoreStates::NO_CHANGE )
  {
    return;
  }

  playerStateManager->changeState(newState);
  setSpeedX(speed.at(getCurrentState()).x);
  setSpeedY(speed.at(getCurrentState()).y);
  handlerAnimation->setCurrentStateForAnimation(getCurrentState());
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();
}
