
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

  handlerAnimation = new Animation(initialFrame, getCurrentState(), SpriteData::RIGHT, 
	                               maxFrame, returnFrame, framerateAnimations );

  collisionHandler = Collider::getInstance();

  delayMovementSprite = delayMovement;

  width = widthSprite;	
  height = heightSprite;
  position.x = pos.x;		
  position.y = pos.y;
  this->speed = speed;
  currentXSpeed = speed.at(getCurrentState()).x;
  currentYSpeed = speed.at(getCurrentState()).y;

  spriteCollisionBox = new CollisionBox(position.x, position.y, 44.0f, 135.0f);
  spriteCollisionBox->setX(position.x, handlerAnimation->getAnimationDirection());
  spriteCollisionBox->setY(position.y);

  changeStatePlayerSprite( new GameCoreStates::FallingState(GameCoreStates::STILL) , 0,
	                       std::list< InputMapping::Key >());

  countX = 0;
  countY = 0;
  characterMovement.playerMoveInXInCurrentFrame = false;
  characterMovement.playerMoveInX = false;
  characterMovement.playerMoveInY = false;

  canMove = true;
}

Sprite::~Sprite(void)
{
  glDeleteTextures(1, &texture);
  speed.clear();
  delete playerStateManager;
}

void Sprite::movePosXWithSpeed()
{
  characterMovement.playerMoveInX = false || characterMovement.playerMoveInX;
  characterMovement.playerMoveInXInCurrentFrame = false;
  countX++;

  if ( countX > delayMovementSprite.at(getCurrentState()).x )
  {
    countX = 0;

		  	  int ydirection = SpriteData::UP;
	  if ( getSpeedY() > 0 )
	  {
		  ydirection = SpriteData::DOWN;
	  }
	  if ( getSpeedY() == 0.0f )
	  {
		  ydirection = SpriteData::NO_DIRECTION;
	  }

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
		  if ( !directionsMove.canMoveXRight )
		  {
			  return;
		  }
        position.x += getSpeedX();
		spriteCollisionBox->setX(position.x, handlerAnimation->getAnimationDirection());
        characterMovement.playerMoveInX = true;
		characterMovement.playerMoveInXInCurrentFrame = true;

				
				bool collision = collisionHandler->onTheGround(*getCollisionBox(), 
					handlerAnimation->getAnimationDirection(), ydirection );
				bool collisionTiles = collisionHandler->checkTileCollision(*getCollisionBox(), 
					handlerAnimation->getAnimationDirection(), ydirection, directionsMove );
				onG = collision;
				canMove = !collisionTiles;

				if ( !directionsMove.canMoveXRight /*collisionTiles*/ && !onG && getCurrentState() == GameCoreStates::FALLING )
				{
					GLfloat temp =  (spriteCollisionBox->getX() + spriteCollisionBox->getWidth())/32;
			int parteEntera = (int)temp;
			GLfloat result = ((temp - parteEntera)*32);
			
			
			position.x -= (result);
			spriteCollisionBox->setX( spriteCollisionBox->getX() - 42 - result, handlerAnimation->getAnimationDirection() );
					changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                     std::list<InputMapping::Key>() );
									changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
				  return;
				}

								if ( !directionsMove.canMoveYUp /*collisionTiles*/ && !onG && getCurrentState() != GameCoreStates::FALLING)
								{
									changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
					               setSpeedX(0.0f);
									return;
								}

								if ( !directionsMove.canMoveXRight/*collisionTiles*/ && onG && getCurrentState() != GameCoreStates::STILL)
					{
							GLfloat temp =  (spriteCollisionBox->getX()+spriteCollisionBox->getWidth())/32;
							int parteEntera = (int)temp;
							GLfloat result = ((temp - parteEntera)*32);
			
							spriteCollisionBox->setX( spriteCollisionBox->getX() - 42 + result, handlerAnimation->getAnimationDirection() );
							position.x += (result);
							changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
													 std::list<InputMapping::Key>() );
							canMove = false;
								characterMovement.playerMoveInY = false;
					characterMovement.playerMoveInX = false;
					return;
						}



		if ( collision && getCurrentState() == GameCoreStates::FALLING )
		{
			GLfloat temp = (spriteCollisionBox->getY() + spriteCollisionBox->getHeight())/32;
			int parteEntera = (int)temp;
			GLfloat result = ((temp - parteEntera)*32);
			
			spriteCollisionBox->setY( spriteCollisionBox->getY() - 45 - result );
			position.y -= (result);
			changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                     std::list<InputMapping::Key>() );
							characterMovement.playerMoveInY = false;
	         characterMovement.playerMoveInX = false;
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
  

	//-------------------------------------------------------------------------------------------------------------------------------------------

    else if ( position.x + getSpeedX() + width  > 0 )
    {
		if ( !directionsMove.canMoveXLeft )
				{
				   return;
				}
      position.x += getSpeedX();
	  spriteCollisionBox->setX(position.x+ (spriteCollisionBox->getWidth()/2), handlerAnimation->getAnimationDirection());
	  
	  
	  canMove = true;
	  characterMovement.playerMoveInX = true;
	  characterMovement.playerMoveInXInCurrentFrame = true;

      bool collision = collisionHandler->onTheGround(*getCollisionBox(), 
					handlerAnimation->getAnimationDirection(), ydirection );
      bool collisionTiles = collisionHandler->checkTileCollision(*getCollisionBox(), 
		            handlerAnimation->getAnimationDirection(), ydirection, 
					directionsMove );

	  if ( !collision )
	  {
		  int d = 4;
	  }

				onG = collision;
				canMove = !collisionTiles;


								if ( !directionsMove.canMoveXLeft /*collisionTiles*/ && !onG && getCurrentState() == GameCoreStates::FALLING )
				{
					GLfloat temp =  (spriteCollisionBox->getX())/32;
			int parteEntera = (int)temp;
			GLfloat result = ((temp - parteEntera)*32);
			
			
			position.x -= (result);
			spriteCollisionBox->setX( spriteCollisionBox->getX() - result, handlerAnimation->getAnimationDirection() );
					changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                     std::list<InputMapping::Key>() );
									changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
				  return;
				}

								if (
									!directionsMove.canMoveYUp && !onG && getCurrentState() != GameCoreStates::FALLING)
								{
									changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
									setSpeedX(0.0f);
									return;
								}
								if ( !directionsMove.canMoveXLeft && getCurrentState() != GameCoreStates::STILL)
		{
			GLfloat temp =  (spriteCollisionBox->getX())/32;
			int parteEntera = (int)temp;
			GLfloat result = ((temp - parteEntera)*32);
			
			
			position.x -= (result);
			spriteCollisionBox->setX( spriteCollisionBox->getX() - result, handlerAnimation->getAnimationDirection() );
			changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                     std::list<InputMapping::Key>() );
			canMove = false;
				characterMovement.playerMoveInY = false;
	characterMovement.playerMoveInX = false;
	return;
		}

		if ( collision && getCurrentState() == GameCoreStates::FALLING )
		{
			GLfloat temp = (spriteCollisionBox->getY() + spriteCollisionBox->getHeight())/32;

			int parteEntera = (int)temp;
			GLfloat result = ((temp - parteEntera)*32);
			
			spriteCollisionBox->setY( spriteCollisionBox->getY() - 45 - result );
			position.y -= (result);
			changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                     std::list<InputMapping::Key>() );

		   characterMovement.playerMoveInY = false;
	       characterMovement.playerMoveInX = false;
		   return;
		}
		if ( !collision && 
					(getCurrentState() != GameCoreStates::JUMPING && 
					getCurrentState() != GameCoreStates::DOUBLE_JUMP && getCurrentState() != GameCoreStates::FALLING &&
					 !(getPreviousState() == GameCoreStates::JUMPING && getCurrentState() == GameCoreStates::FAST_ATTACK) ) )
		{
		   changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
		   return;
		}
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
	  	  int ydirection = SpriteData::UP;
	  if ( getSpeedY() > 0 )
	  {
		  ydirection = SpriteData::DOWN;
		  if ( !directionsMove.canMoveYDown )
		  {
			  return;
		  }


	  }

	  else  if ( !directionsMove.canMoveYUp )
		  {
			  return;
		  }
	  position.y += getSpeedY();
	  spriteCollisionBox->setY(position.y);
	  GamePhysics::PhysicsCore::getInstance()->physicManager(&currentYSpeed, 
		                                       GamePhysics::PARABOLIC, getCurrentState() );

	  characterMovement.playerMoveInY = true;
	  characterMovement.playerMoveInYInCurrentFrame = true;


	  bool collision = collisionHandler->onTheGround(*getCollisionBox(),
			                                          handlerAnimation->getAnimationDirection(),
													  ydirection);
      bool collisionTiles = collisionHandler->checkTileCollision(*getCollisionBox(), 
					                                  handlerAnimation->getAnimationDirection(), 
													  ydirection, directionsMove);
     onG = collision;

	 if ( !directionsMove.canMoveYUp && !onG && getCurrentState() != GameCoreStates::FALLING)
								{
									changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
									setSpeedX(0.0f);
									return;
								}

		if ( collision && getCurrentState() == GameCoreStates::FALLING )
		{
			GLfloat temp = (spriteCollisionBox->getY() + spriteCollisionBox->getHeight())/32;
			int parteEntera = (int)temp;
		   GLfloat result = ((temp - parteEntera)*32);
			
		   spriteCollisionBox->setY( spriteCollisionBox->getY() - 45 - result );
           position.y -= (result);

		   changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                   std::list<InputMapping::Key>() );
		   characterMovement.playerMoveInY = false;
	       characterMovement.playerMoveInX = false;

		   return;
		}
		if ( !collision && !directionsMove.canMoveYUp &&
					(getCurrentState() != GameCoreStates::JUMPING && 
					getCurrentState() != GameCoreStates::DOUBLE_JUMP && getCurrentState() != GameCoreStates::FALLING &&
					 !(getPreviousState() == GameCoreStates::JUMPING && getCurrentState() == GameCoreStates::FAST_ATTACK) ) )
		{
		
		   changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                     std::list<InputMapping::Key>() );
		   return;
		}

	  return;
    }
	currentYSpeed = 0.0f;
	characterMovement.playerMoveInX = false;
	characterMovement.playerMoveInY = false;
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
	if ( getPreviousState() == GameCoreStates::JUMPING )
	{
      speed.at(getCurrentState()).x = speed.at(getPreviousState()).x/2;
	}
	else
	{
	  speed.at(getCurrentState()).x = speed.at(getPreviousState()).x;
	}
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

  if ( resultCheckingEqualStates == GameCoreStates::UPDATE_SPEEDX )
		{
			playerStateManager->changePreviousState( GameCoreStates::WALKING );

			setSpeedX( speed.at( GameCoreStates::WALKING ).x );
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
  setSpeedY(speed.at(getCurrentState()).y);
  handlerAnimation->setCurrentStateForAnimation(getCurrentState());
  handlerAnimation->restartOldTime();
  handlerAnimation->restartCurrentFrame();
  handlerAnimation->restartAnimationBegin();
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




