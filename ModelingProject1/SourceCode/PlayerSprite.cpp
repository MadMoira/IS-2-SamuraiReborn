#include "PlayerSprite.h"

PlayerSprite::PlayerSprite(SpriteData::IDSprites id, std::string filename, std::vector< Vector2f > speed, Vector2f pos, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
				GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
				std::vector< Vector2f> delayMovement) : Sprite(id, filename, speed, pos, initialFrame, maxFrame,
				                                               returnFrame, widthSprite, heightSprite, framerateAnimations,
															   delayMovement)
{
}

void PlayerSprite::changeStateSprite(GameCoreStates::PlayerState* newState, int keyPreviouslyPressed, 
                                     std::list<InputMapping::Key> keys)
{
  int resultCheckingEqualStates = newState->checkIfEqualStates(keys, getCurrentState(),
		                            getPreviousState(), newState, keyPreviouslyPressed);

  switch(resultCheckingEqualStates)
  {
    case GameCoreStates::UPDATE_SPEEDX:
    {
      playerStateManager->changePreviousState( GameCoreStates::WALKING );
      setSpeedX( speed.at( GameCoreStates::WALKING ).x );
      return;
    }
    case GameCoreStates::NO_CHANGE:
    {
      return;
    }
  }

  int result = newState->checkMovementRestrictions(keyPreviouslyPressed, getPreviousState(), 
                                                   getCurrentState(), keys );

  switch(result)
  {
    case GameCoreStates::NO_CHANGE:
    {
      return;
    }
    case GameCoreStates::CHANGE:
    {
      playerStateManager->changeState(newState);
      break;
    }
    case GameCoreStates::RETURN_STILL:
    {
      playerStateManager->changeState(STILL_STATE);
	  break;
    }
	case GameCoreStates::RETURN_STOPPING:
    {
      playerStateManager->changeState(STOPPING_STATE);
	  break;
    }
	case GameCoreStates::RETURN_WALKING:
    {
      playerStateManager->changeState(WALKING_STATE);
      break;
    }
  }

  setSpeedX(speed.at(getCurrentState()).x);
  setSpeedY(speed.at(getCurrentState()).y);
  handlerAnimation->setCurrentStateForAnimation(getCurrentState());
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();
}