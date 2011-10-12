
#include "Sprite.h"
#include "PlayerState.h"

Sprite::Sprite(IDSprites id, std::string filename, std::vector< Vector2f > speed, Vector2f pos, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame,
				GLfloat widthSprite, GLfloat heightSprite)
{
  texture = GameRender::loadTexture(filename);
  glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &this->widthTexture);
  glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &this->heightTexture);

  playerStateManager = new PlayerStateManager();
  playerStateManager->pushState( new GameCoreStates::PlayerState(GameCoreStates::STILL) );

  handlerAnimation = new Animation(initialFrame, maxFrame.at(getCurrentState()), 
		                           returnFrame.at(getCurrentState()), 
								   SpriteData::RIGHT );

  maxFramesPerAnimation = maxFrame;
  returnFramesPerAnimation = returnFrame;

  width = widthSprite;	
  height = heightSprite;
  position.x = pos.x;		
  position.y = pos.y;
  this->speed = speed;
  currentXSpeed = speed.at(getCurrentState()).x;
  currentYSpeed = speed.at(getCurrentState()).y;
  delay.x = 0;
  delay.y = 0;
}

Sprite::~Sprite(void)
{
  glDeleteTextures(1, &texture);
  maxFramesPerAnimation.clear();
  returnFramesPerAnimation.clear();
  speed.clear();
  delete playerStateManager;
}

bool Sprite::movePosXWithSpeed()
{
  if ( position.x + getSpeedX() + width < 6368.f )
  {
    position.x += getSpeedX();
    return true;
  }

  return false;
}

bool Sprite::movePosYWithSpeed()
{
  if( position.y + getSpeedY()+height < 550.f )
  {
    position.y += getSpeedY();
    return true;
  }

  return false;
}

void Sprite::setSpeedX(GLfloat speedX)
{
  if ( getCurrentState() == GameCoreStates::JUMPING || getCurrentState() == GameCoreStates::DOUBLE_JUMP)
  {
    speed.at(getCurrentState()).x = speedX;
  }

  currentXSpeed = speedX;
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
  if ( playerStateManager->getCurrentState() == newState->getCurrentID() )
  {
    return;
  }

  int result = newState->checkMovementRestrictions(keyPreviouslyPressed, getPreviousState(), 
                                                   getCurrentState(), keys );

  if ( result == GameCoreStates::CHANGE )
  {
    playerStateManager->changeState(newState);

    setSpeedY(speed.at(getCurrentState()).y);
    handlerAnimation->setLoopPerAnimation(0);
    handlerAnimation->setMaxFrame( maxFramesPerAnimation.at(getCurrentState()) );
    handlerAnimation->setReturnFrame( returnFramesPerAnimation.at(getCurrentState()) );	
    return;
  }

  else if( result == GameCoreStates::RETURN_STILL )
  {
    playerStateManager->changeState(STILL_STATE);
    setSpeedY(speed.at(getCurrentState()).y);
    handlerAnimation->setLoopPerAnimation(0);
    handlerAnimation->setMaxFrame( maxFramesPerAnimation.at(getCurrentState()) );
    handlerAnimation->setReturnFrame( returnFramesPerAnimation.at(getCurrentState()) );
	return;
  }
}

void Sprite::drawTexture()
{
  GameRender::drawSpriteTexture(texture, position,  handlerAnimation->getCurrentFrame(), 
                                widthTexture, heightTexture, width, height, 
                                handlerAnimation->getAnimationDirection(), getCurrentState() );
}




