
#include "Sprite.h"
#include "PlayerState.h"
#include "Collider.h"
#include "Camera.h"

#include "PhysicsCore.h"

Sprite::Sprite(IDSprites id, std::string filename, std::vector< Vector2f > speed, Vector2f pos, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
				GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
				std::vector< Vector2f> delayMovement)
{
  texture = GameRender::loadTexture(filename);
  glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &this->widthTexture);
  glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &this->heightTexture);

  playerStateManager = new GameCoreStates::PlayerStateManager();
  playerStateManager->pushState( new GameCoreStates::PlayerState(GameCoreStates::STILL) );

  handlerAnimation = new Animation(initialFrame, maxFrame.at(getCurrentState()), 
		                           returnFrame.at(getCurrentState()), 
								   framerateAnimations.at(getCurrentState()),
								   SpriteData::RIGHT );

  collisionHandler = Collider::getInstance();

  maxFramesPerAnimation = maxFrame;
  returnFramesPerAnimation = returnFrame;
  frameratePerAnimation =  framerateAnimations;
  delayMovementSprite = delayMovement;

  width = widthSprite;	
  height = heightSprite;
  position.x = pos.x;		
  position.y = pos.y;
  this->speed = speed;
  currentXSpeed = speed.at(getCurrentState()).x;
  currentYSpeed = speed.at(getCurrentState()).y;

  spriteCollisionBox = new CollisionBox(position.x, position.y, 44.0f, 135.0f);
  spriteCollisionBox->setX(position.x);
  spriteCollisionBox->setY(position.y);

  countX = 0;
  countY = 0;
  playerMoveInXInCurrentFrame = false;
  playerMoveInX = false;
  playerMoveInY = false;
}

Sprite::~Sprite(void)
{
  glDeleteTextures(1, &texture);
  maxFramesPerAnimation.clear();
  returnFramesPerAnimation.clear();
  speed.clear();
  delete playerStateManager;
}

void Sprite::movePosXWithSpeed()
{
  playerMoveInX = false || playerMoveInX;
  playerMoveInXInCurrentFrame = false;
  countX++;

  if ( countX > delayMovementSprite.at(getCurrentState()).x )
  {
    countX = 0;
	spriteCollisionBox->setX( position.x + getSpeedX() );

	if ( Camera::getInstance()->isLimit(position.x, getSpeedX()) )
	{ 
	  playerMoveInX = false;
	  playerMoveInXInCurrentFrame = false;
	  return;
	}
    if ( handlerAnimation->getAnimationDirection() == SpriteData::RIGHT )
    {
      if ( position.x + getSpeedX() + width < 6400.f )
      {
		  		        position.x += getSpeedX();
		spriteCollisionBox->setX(position.x);
        playerMoveInX = true;
		playerMoveInXInCurrentFrame = true;

				
				bool collision = collisionHandler->onTheGround(*getCollisionBox(), 
					handlerAnimation->getAnimationDirection() );
				onG = collision;

		if ( collision && getCurrentState() == GameCoreStates::FALLING )
		{
			GLfloat temp = (spriteCollisionBox->getY() + spriteCollisionBox->getHeight())/32;
			int parteEntera = (int)temp;
			GLfloat result = ((temp - parteEntera)*32);
			
			spriteCollisionBox->setY( spriteCollisionBox->getY() - 45 - result );
			position.y -= (result);
			changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                     std::list<InputMapping::Key>() );
							playerMoveInY = false;
	         playerMoveInX = false;
		   return;
		}



		if ( !collision &&
					(getCurrentState() != GameCoreStates::JUMPING && 
					getCurrentState() != GameCoreStates::DOUBLE_JUMP && 
					getCurrentState() != GameCoreStates::FALLING && !(getPreviousState() == GameCoreStates::JUMPING && getCurrentState() == GameCoreStates::FAST_ATTACK) ) )
		{
		   changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );

		   return;
		}


		return;
      }
    }
  
    else if ( position.x + getSpeedX() + width  > 0 )
    {
      position.x += getSpeedX();
	  spriteCollisionBox->setX(position.x-spriteCollisionBox->getWidth()/2);
	  playerMoveInX = true;
	  playerMoveInXInCurrentFrame = true;

	  			bool collision = collisionHandler->onTheGround(*getCollisionBox(), 
					handlerAnimation->getAnimationDirection() );
				onG = collision;



		if ( collision && getCurrentState() == GameCoreStates::FALLING )
		{
			GLfloat temp = (spriteCollisionBox->getY() + spriteCollisionBox->getHeight())/32;
			int parteEntera = (int)temp;
			GLfloat result = ((temp - parteEntera)*32);
			
			spriteCollisionBox->setY( spriteCollisionBox->getY() - 45 - result );
			position.y -= (result);
			changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                     std::list<InputMapping::Key>() );
				playerMoveInY = false;
	playerMoveInX = false;
		   return;
		}
		if ( !collision &&
					(getCurrentState() != GameCoreStates::JUMPING && 
					getCurrentState() != GameCoreStates::DOUBLE_JUMP && getCurrentState() != GameCoreStates::FALLING &&
					 (getPreviousState() != GameCoreStates::JUMPING && getCurrentState() == GameCoreStates::FAST_ATTACK) ) )
		{
		   changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
		   return;
		}
	  return;
    }

	spriteCollisionBox->setX( position.x - getSpeedX() );
	playerMoveInX = false;
  }
}

void Sprite::movePosYWithSpeed()
{
  playerMoveInY = false || playerMoveInY;
  playerMoveInYInCurrentFrame = false;
  countY++;
  if ( countY > delayMovementSprite.at(getCurrentState()).y )
  {

    countY = 0;
	spriteCollisionBox->setY( position.y + getSpeedY() );
    if( position.y + getSpeedY() + height <= 1000.0f )
    {
		      position.y += getSpeedY();
	  spriteCollisionBox->setY(position.y);
	  GamePhysics::PhysicsCore::getInstance()->physicManager(&currentYSpeed, 
		                         GamePhysics::PARABOLIC, getCurrentState() );
	  playerMoveInY = true;
	  playerMoveInYInCurrentFrame = true;


		bool collision = collisionHandler->onTheGround(*getCollisionBox(),
			handlerAnimation->getAnimationDirection());
		onG = collision;

		if ( collision && getCurrentState() == GameCoreStates::FALLING )
		{
			GLfloat temp = (spriteCollisionBox->getY() + spriteCollisionBox->getHeight())/32;
			int parteEntera = (int)temp;
			GLfloat result = ((temp - parteEntera)*32);
			
			spriteCollisionBox->setY( spriteCollisionBox->getY() - 45 - result );
			position.y -= (result);
		   changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                     std::list<InputMapping::Key>() );
		   playerMoveInY = false;
	       playerMoveInX = false;

		   return;
		}
	  	  		if ( !collision &&
					(getCurrentState() != GameCoreStates::JUMPING && 
					getCurrentState() != GameCoreStates::DOUBLE_JUMP && getCurrentState() != GameCoreStates::FALLING &&
					 (getPreviousState() != GameCoreStates::JUMPING && getCurrentState() == GameCoreStates::FAST_ATTACK) ) )
		{
		
		   changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
		   return;
		}

	  return;
    }
	spriteCollisionBox->setY( position.y - getSpeedY() );
	currentYSpeed = 0.0f;
	playerMoveInY = false;
	playerMoveInX = false;
  }
}

void Sprite::setSpeedX(GLfloat speedX)
{
  if ( getCurrentState() == GameCoreStates::JUMPING || getCurrentState() == GameCoreStates::DOUBLE_JUMP ||
	   getCurrentState() == GameCoreStates::FALLING )
  {
    speed.at(getCurrentState()).x = speedX;
  }

  if ( getCurrentState() == GameCoreStates::FAST_ATTACK )
  {
	speed.at(getCurrentState()).x = speed.at(getPreviousState()).x;
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

void Sprite::changeStatePlayerSprite(GameCoreStates::PlayerState* newState, int keyPreviouslyPressed, 
                                     std::list<InputMapping::Key> keys)
{
  int resultCheckingEqualStates = newState->checkIfEqualStates(keys, getCurrentState(),
		                            getPreviousState(), newState, keyPreviouslyPressed);
  if ( resultCheckingEqualStates == GameCoreStates::NO_CHANGE )
  {
    return;
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
  }

  setSpeedY(speed.at(getCurrentState()).y);
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();
  handlerAnimation->setFrameRate( frameratePerAnimation.at(getCurrentState()) );
  handlerAnimation->setMaxFrame( maxFramesPerAnimation.at(getCurrentState()) );
  handlerAnimation->setReturnFrame( returnFramesPerAnimation.at(getCurrentState()) );
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
  setSpeedY(speed.at(getCurrentState()).y);
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();
  handlerAnimation->setFrameRate( frameratePerAnimation.at(getCurrentState()) );
  handlerAnimation->setMaxFrame( maxFramesPerAnimation.at(getCurrentState()) );
  handlerAnimation->setReturnFrame( returnFramesPerAnimation.at(getCurrentState()) );	
}

void Sprite::drawTexture()
{
  GLfloat x = getBoxX();
  if( x < 0 )
  {
	  x = 0;
  }
  GLfloat y = getBoxY();
  
  GameRender::drawFullTexture(GameRender::loadTexture("box.png"), Vector2f(x, y), 44, 135);

  int currentState = getCurrentState();

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
                                widthTexture, heightTexture, width, height, 
								handlerAnimation->getAnimationDirection(), currentState );


}




