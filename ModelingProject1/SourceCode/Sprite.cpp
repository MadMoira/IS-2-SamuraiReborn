
#include "Sprite.h"
#include "PlayerState.h"
#include "Collider.h"
#include "Camera.h"

Sprite::Sprite(IDSprites id, std::string filename, std::vector< Vector2f > speed, Vector2f pos, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
				GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
				std::vector< Vector2f> delayMovement)
{
  texture = GameRender::loadTexture(filename);
  glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &this->widthTexture);
  glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &this->heightTexture);

  playerStateManager = new GameCoreStates::PlayerStateManager();

  handlerAnimation = new Animation(initialFrame, getCurrentState(), SpriteData::RIGHT, 
	                               maxFrame, returnFrame, framerateAnimations );

  rigidBody = new GamePhysics::RigidBody(GamePhysics::RIGID_BODY);
  rigidBody->initializeNaturalPhysicsForces(-4.0f, 2.0f);

  collisionHandler = Collider::getInstance();

  delayMovementSprite = delayMovement;

  width = widthSprite;	
  height = heightSprite;
  position.x = pos.x;		
  position.y = pos.y;
  this->speed = speed;
  currentXSpeed = speed.at(getCurrentState()).x;
  currentYSpeed = speed.at(getCurrentState()).y;

  //spriteCollisionBox = new CollisionSystem::CollisionBox(0.0f, 0.0f, 44.0f, 135.0f, Vector2f(42.0f, 45.0f)); //- Meerkat
  spriteCollisionBox = new CollisionSystem::CollisionBox(0.0f, 0.0f, 90.0f, 160.0f, Vector2f(92.0f, 42.0f));
  spriteCollisionBox->setX(position.x, handlerAnimation->getAnimationDirection());
  spriteCollisionBox->setY(position.y);

  changeStatePlayerSprite( new GameCoreStates::StillState(GameCoreStates::STILL) , 0,
	                       std::list< InputMapping::Key >());

  countX = 0;
  countY = 0;

  characterMovement.playerMoveInXInCurrentFrame = false;
  characterMovement.playerMoveInYInCurrentFrame = false;
  characterMovement.playerMoveInX = false;
  characterMovement.playerMoveInY = false;
}

Sprite::~Sprite(void)
{
  glDeleteTextures(1, &texture);
  speed.clear();
  delayMovementSprite.clear();
  delete rigidBody;
  delete playerStateManager;
  delete handlerAnimation;
  delete spriteCollisionBox;
}

void Sprite::movePosXWithSpeed()
{
  characterMovement.playerMoveInX = false || characterMovement.playerMoveInX;
  characterMovement.playerMoveInXInCurrentFrame = false;
  countX++;

  if ( countX > delayMovementSprite.at(getCurrentState()).x )
  {
    countX = 0;
	handlerAnimation->changeDirectionY( getSpeedY() );

	if ( Camera::getInstance()->isLimit(position.x, getSpeedX()) )
	{ 
	  characterMovement.playerMoveInX = false;
	  characterMovement.playerMoveInXInCurrentFrame = false;
	  return;
	}

    if ( handlerAnimation->getAnimationDirection() == SpriteData::RIGHT )
    {
      if ( position.x + getSpeedX() + width < 6400.f )
      {
        if ( !directionsMove.canMoveXRight || getSpeedX() == 0.0f)
        {
          return;
        }

        position.x += getSpeedX();
		spriteCollisionBox->setX(position.x, handlerAnimation->getAnimationDirection());

		if ( spriteCollisionBox->getX() + spriteCollisionBox->getWidth() >= 73*32 )
		{
			int d = 4;
		}

        characterMovement.playerMoveInX = true;
		characterMovement.playerMoveInXInCurrentFrame = true;

		rigidBody->applyNaturalPhysicForces(GamePhysics::X, &currentXSpeed, &currentYSpeed, 
			                                getCurrentState(), handlerAnimation->getAnimationDirection());

        isOnGround = collisionHandler->onTheGround(*getCollisionBox(), 
					                   handlerAnimation->getAnimationDirection(), handlerAnimation->getDirectionY() );
		collisionHandler->checkTileCollision(*getCollisionBox(), 
					                   handlerAnimation->getAnimationDirection(), handlerAnimation->getDirectionY(), 
									   directionsMove);

		collisionHandler->checkStateCollisionXAxis(*this);

        return;
      }
    }

    else if ( position.x + getSpeedX() + width  > 0 )
    {
      if ( !directionsMove.canMoveXLeft || getSpeedX() == 0.0f )
      {
        return;
      }

      position.x += getSpeedX();
	  spriteCollisionBox->setX(position.x + spriteCollisionBox->getOffset().x, handlerAnimation->getAnimationDirection());

	  rigidBody->applyNaturalPhysicForces(GamePhysics::X, &currentXSpeed, &currentYSpeed, 
		                                  getCurrentState(), handlerAnimation->getAnimationDirection());

	  characterMovement.playerMoveInX = true;
	  characterMovement.playerMoveInXInCurrentFrame = true;

      isOnGround = collisionHandler->onTheGround(*getCollisionBox(), 
		                             handlerAnimation->getAnimationDirection(), handlerAnimation->getDirectionY() );
      collisionHandler->checkTileCollision(*getCollisionBox(), 
		                             handlerAnimation->getAnimationDirection(), handlerAnimation->getDirectionY(), 
					                 directionsMove);

	  collisionHandler->checkStateCollisionXAxis(*this);

	  return;
    }
	characterMovement.playerMoveInX = false;
  }
}

void Sprite::movePosYWithSpeed()
{
  characterMovement.playerMoveInY = false || characterMovement.playerMoveInY;
  characterMovement.playerMoveInYInCurrentFrame = false;
  countY++;

  if ( countY > delayMovementSprite.at(getCurrentState()).y )
  {
    countY = 0;
    if( position.y + getSpeedY() + height <= 1000.0f )
    {
      handlerAnimation->changeDirectionY( getSpeedY() );
      
      if ( !getPlayerDirectionYBasedInDirection() )
      {
        return;
      }

	  position.y += getSpeedY();
	  spriteCollisionBox->setY(position.y);

	  rigidBody->applyNaturalPhysicForces(GamePhysics::Y, &currentXSpeed, &currentYSpeed, 
		                                  getCurrentState(), handlerAnimation->getAnimationDirection());

	  characterMovement.playerMoveInY = true;
	  characterMovement.playerMoveInYInCurrentFrame = true;

	  isOnGround = collisionHandler->onTheGround(*getCollisionBox(),
			                         handlerAnimation->getAnimationDirection(), handlerAnimation->getDirectionY());
      collisionHandler->checkTileCollision(*getCollisionBox(), 
                                     handlerAnimation->getAnimationDirection(), 
                                     handlerAnimation->getDirectionY(), directionsMove);

	  collisionHandler->checkStateCollisionPlayer(*this);
	  return;
    }

	currentYSpeed = 0.0f;
	characterMovement.playerMoveInX = false;
	characterMovement.playerMoveInY = false;
  }
}

bool Sprite::getPlayerMoveBasedInDirection()
{
  if ( handlerAnimation->getAnimationDirection() == SpriteData::RIGHT)
  {
    return directionsMove.canMoveXRight;
  }
  return directionsMove.canMoveXLeft;
}

bool Sprite::getPlayerDirectionYBasedInDirection()
{
  if ( handlerAnimation->getDirectionY() == SpriteData::UP )
  {
    return directionsMove.canMoveYUp;
  }
  return directionsMove.canMoveYDown;
}

void Sprite::setSpeedX(GLfloat speedX)
{
  switch( getCurrentState() )
  {
    case GameCoreStates::JUMPING:
    case GameCoreStates::DOUBLE_JUMP:
    case GameCoreStates::FALLING:
    {
      speed.at(getCurrentState()).x = speedX;
      break;
    }
    case GameCoreStates::FAST_ATTACK:
    {
      if ( getPreviousState() == GameCoreStates::JUMPING )
      {
        speed.at(getCurrentState()).x = speed.at(getPreviousState()).x/2;
        break;
      }
      speed.at(getCurrentState()).x = speed.at(getPreviousState()).x;
      break;
    }
  }

  if ( !getPlayerMoveBasedInDirection() )
  {
    currentXSpeed = 0.0f;
    return;
  }

  currentXSpeed = speed.at(getCurrentState()).x;
}

void Sprite::setSpeedY(GLfloat speedY)
{
  if ( getCurrentState() == GameCoreStates::FAST_ATTACK )
  {
    if ( getPreviousState() == GameCoreStates::JUMPING )
    {
	  speedY = -4.0f;
      speed.at(getCurrentState()).y = speedY;
    }

	else
	{
	  speedY = 0.0f;
	  speed.at(getCurrentState()).y = speedY;	  
    }
  }

  currentYSpeed = speedY;
}

void Sprite::setConstantSpeedX(int constant)
{
  for(std::string::size_type i = 0; i < speed.size(); i++)
  {
    speed.at(i).x *= constant;
  }

  currentXSpeed *= constant;
}

void Sprite::changeCurrentFrame(int frame)
{
  handlerAnimation->setCurrentFrame(frame);
}

void Sprite::changePreviousPlayerState(int stateID)
{
  playerStateManager->changePreviousState( GameCoreStates::SpriteState(stateID) );
}

void Sprite::changeStatePlayerSprite(GameCoreStates::PlayerState* newState, int keyPreviouslyPressed, 
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

void Sprite::changeStateEnemySprite(GameCoreStates::PlayerState* newState)
{
  int resultCheckingEqualStates = newState->checkIfEqualStates(std::list<InputMapping::Key>(), getCurrentState(),
		                          getPreviousState(), newState, 0);
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

bool Sprite::isPlayerOnTheAir()
{
  if ( getCurrentState() != GameCoreStates::JUMPING && 
       getCurrentState() != GameCoreStates::DOUBLE_JUMP && 
       getCurrentState() != GameCoreStates::FALLING && 
       !(getPreviousState() == GameCoreStates::JUMPING && getCurrentState() == GameCoreStates::FAST_ATTACK) )
  {
    return false;
  }
  return true;
}

void Sprite::drawTexture()
{
  GLfloat x = getBoxX();
  if( x < 0 )
  {
    x = 0;
  }
  GLfloat y = getBoxY();
  
  //GameRender::drawFullTexture(GameRender::loadTexture("box.png"), Vector2f(x, y), 44, 135);
  GameRender::drawFullTexture(GameRender::loadTexture("boxPanda.png"), Vector2f(x, y), 90, 160);

  int currentState = getCurrentState();
  
  if ( currentState == GameCoreStates::STOPPING )
  {
    currentState = GameCoreStates::WALKING;
  }

  if ( currentState == GameCoreStates::DOUBLE_JUMP )
  {
    currentState = GameCoreStates::JUMPING;
  }

  if ( getCurrentState() == GameCoreStates::FAST_ATTACK )
  {
    currentState = ( GameCoreStates::FAST_ATTACK - 1 ) + getPreviousState();
  }

  if ( getCurrentState() == GameCoreStates::FALLING )
  {
	currentState = 8;
  }

  GameRender::drawSpriteTexture(texture, position,  handlerAnimation->getCurrentFrame(), 
	                            widthTexture, heightTexture, width, height, spriteCollisionBox->getWidth(), 
								handlerAnimation->getAnimationDirection(), currentState );
}




