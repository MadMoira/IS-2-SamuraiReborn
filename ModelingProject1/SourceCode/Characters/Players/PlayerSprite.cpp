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

  if ( getPreviousState() == GameCoreStates::RUNNING && getCurrentState() == GameCoreStates::JUMPING )
  {
	  int d = 4;
  }
  if ( getSpeedX() > 0.0f)
  {
    	  GameCoreStates::ConditionsPlayerRunning isPacing = playerStateManager->getObjectState().checkIfPlayerIsRunning(keys);
	  if ( isPacing.directionButtonPressed && getCurrentState() == GameCoreStates::WALKING)
	  {
		  rigidBody->setAccelerationState(1);
	  }

	  if ( isPacing.directionButtonPressed && !isPacing.runningButtonPressed && getCurrentState() == GameCoreStates::RUNNING)
	  {
		  if ( getSpeedX() > 10.0f )
		  {
		  rigidBody->setAccelerationState(2);
		  return;
		  }
		  int d = 4;
	  }
	  else if ( !isPacing.directionButtonPressed && getCurrentState() == GameCoreStates::WALKING && newState->getCurrentID() != GameCoreStates::FALLING) 
	  {
		  rigidBody->setAccelerationState(2);
		  return;
	  }

	  if ( isPacing.directionButtonPressed && isPacing.runningButtonPressed && getCurrentState() == GameCoreStates::RUNNING)
	  {
		  rigidBody->setAccelerationState(1);
	  }
	  else if ( ( (!isPacing.directionButtonPressed && !isPacing.runningButtonPressed) || (!isPacing.directionButtonPressed && isPacing.runningButtonPressed) )
		  && getCurrentState() == GameCoreStates::RUNNING && newState->getCurrentID() != GameCoreStates::FALLING) 
	  {
		  rigidBody->setAccelerationState(2);
		  return;
	  }
  }
  switch(resultCheckingEqualStates)
  {
    case GameCoreStates::UPDATE_SPEEDX:
    {
		if ( getSpeedX() == 0.0f )
		{
      playerStateManager->changePreviousState( GameCoreStates::WALKING );
      setSpeedX( speed.at( GameCoreStates::WALKING ).x + 5.0f );
	  rigidBody->setAccelerationState(1);
		}
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
    case GameCoreStates::RETURN_WALKING:
    {
      playerStateManager->changeState(WALKING_STATE);
      break;
    }
  }

  if ( getCurrentState() == GameCoreStates::WALKING && getSpeedX() == 0.0f )
  {
	setSpeedX( speed.at( GameCoreStates::WALKING ).x );
  }

  if ( getCurrentState() != GameCoreStates::WALKING && getCurrentState() != GameCoreStates::RUNNING && 
	  getCurrentState() != GameCoreStates::STILL && getCurrentState() != GameCoreStates::FAST_ATTACK && 
	  getCurrentState() != GameCoreStates::JUMPING && getCurrentState() != GameCoreStates::FALLING && 
	  getCurrentState() != GameCoreStates::DOUBLE_JUMP)
  {
  setSpeedX(speed.at(getCurrentState()).x);
  }



  setSpeedY(speed.at(getCurrentState()).y);
  handlerAnimation->setCurrentStateForAnimation(getCurrentState());
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();
}