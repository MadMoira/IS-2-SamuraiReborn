
#include "Sprite.h"
#include "PlayerState.h"

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

  countX = 0;
  countY = 0;

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

  countX++;
  if ( countX > delayMovementSprite.at(getCurrentState()).x )
  {
    countX = 0;
    if ( handlerAnimation->getAnimationDirection() == SpriteData::RIGHT )
    {
      if ( position.x + getSpeedX() + width < 6368.f )
      {
        position.x += getSpeedX();
		playerMoveInX = true;
		return;
      }
    }
  
    else if ( position.x + getSpeedX() + width  > 0 )
    {
      position.x += getSpeedX();
	  playerMoveInX = true;
	  return;
    }
	playerMoveInX = false;
  }
}

void Sprite::movePosYWithSpeed()
{
  playerMoveInY = false || playerMoveInY;

  countY++;
  if ( countY > delayMovementSprite.at(getCurrentState()).y )
  {
    countY = 0;
    if( position.y + getSpeedY() + height < 550.f )
    {
      position.y += getSpeedY();
	  playerMoveInY = true;
	  return;
    }
	playerMoveInY = false;
	playerMoveInX = false;
  }
}

void Sprite::setSpeedX(GLfloat speedX)
{
  if ( getCurrentState() == GameCoreStates::JUMPING || getCurrentState() == GameCoreStates::DOUBLE_JUMP)
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
  if ( getPreviousState() == GameCoreStates::FAST_ATTACK &&
	   getCurrentState() == GameCoreStates::JUMPING)
  {
	currentYSpeed = speedY;
  }
  if ( getCurrentState() == GameCoreStates::FAST_ATTACK )
  {
	speed.at(getCurrentState()).y = currentYSpeed;
	speedY = currentYSpeed;
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
		                            getPreviousState(), newState);
  if ( resultCheckingEqualStates == GameCoreStates::NO_CHANGE )
  {
    return;
  }

  int result = newState->checkMovementRestrictions(keyPreviouslyPressed, getPreviousState(), 
                                                   getCurrentState(), keys );

  if ( result == GameCoreStates::CHANGE )
  {
    playerStateManager->changeState(newState);

    setSpeedY(speed.at(getCurrentState()).y);

	handlerAnimation->restartOldTime();
	handlerAnimation->restartCurrentFrame();
	handlerAnimation->setFrameRate( frameratePerAnimation.at(getCurrentState()) );
    handlerAnimation->setMaxFrame( maxFramesPerAnimation.at(getCurrentState()) );
    handlerAnimation->setReturnFrame( returnFramesPerAnimation.at(getCurrentState()) );	
    return;
  }

  else if( result == GameCoreStates::RETURN_STILL )
  {
    playerStateManager->changeState(STILL_STATE);

    setSpeedY(speed.at(getCurrentState()).y);
	handlerAnimation->restartOldTime();
	handlerAnimation->restartCurrentFrame();
	handlerAnimation->setFrameRate( frameratePerAnimation.at(getCurrentState()) );
    handlerAnimation->setMaxFrame( maxFramesPerAnimation.at(getCurrentState()) );
    handlerAnimation->setReturnFrame( returnFramesPerAnimation.at(getCurrentState()) );
	return;
  }
}

void Sprite::drawTexture()
{
	if ( getCurrentState() == GameCoreStates::FAST_ATTACK )
	{
	 GameRender::drawSpriteTexture(texture, position,  handlerAnimation->getCurrentFrame(), 
                                widthTexture, heightTexture, width, height, 
								handlerAnimation->getAnimationDirection(), getCurrentState() + (getPreviousState()-1) );
	}
	else
	{
  GameRender::drawSpriteTexture(texture, position,  handlerAnimation->getCurrentFrame(), 
                                widthTexture, heightTexture, width, height, 
								handlerAnimation->getAnimationDirection(), getCurrentState() );}
}




