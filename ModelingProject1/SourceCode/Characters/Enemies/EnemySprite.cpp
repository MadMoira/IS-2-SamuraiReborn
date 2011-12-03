
#include "EnemySprite.h"

EnemySprite::EnemySprite(SpriteData::IDSprites id, std::string filename, Vector2f pos, 
                int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement) : Sprite(id, filename, pos, initialFrame, maxFrame,
                                                               returnFrame, widthSprite, heightSprite, framerateAnimations,
                                                               delayMovement)
{
}

void EnemySprite::changeStateSprite(GameCoreStates::PlayerState* newState, int keyPreviouslyPressed, 
                                    std::list<InputMapping::Key> keys, InputMapping::Controller& controller)
{
  int resultCheckingEqualStates = newState->checkIfEqualStates(controller, keys, getCurrentState(),
                                  getPreviousState(), newState, keyPreviouslyPressed);

  if ( resultCheckingEqualStates == GameCoreStates::NO_CHANGE )
  {
    return;
  }

  playerStateManager->changeState(newState);
  setSpeedX(rigidBody->getMaxSpeed().at(getCurrentState()).x);
  setSpeedY(rigidBody->getMaxSpeed().at(getCurrentState()).y);
  handlerAnimation->setCurrentStateForAnimation(getCurrentState());
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();
}
