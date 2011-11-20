
#include "MeerkatP2.h"

MeerkatP2::~MeerkatP2()
{
  delete playerSprite;
  delete inputMapper;
  delete stats;
  delete score;
}

void MeerkatP2::initializePlayer(SpriteData::IDSprites id, std::string filename, std::vector< Vector2f > speed,
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
				std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  playerSprite = new Sprite(id, filename, speed, pos, initialFrame, maxFrame, returnFrame,
							widthSprite, heightSprite, framerateAnimations, delayMovement);
  inputMapper = new InputMapping::GameInputMapper();
  inputMapper->pushContext("maincontext");
  inputMapper->addCallback( Player::inputCallback, 0);
}

void MeerkatP2::noAction()
{
  playerSprite->setSpeedX(0.0f);
  playerSprite->setPlayerMoveInX(false);
  playerSprite->setPlayerMoveInY(false);
  playerSprite->setPlayerMoveInXCurrentFrame(false);
  stop();	
}

void MeerkatP2::walk()
{
  playerSprite->setSpeedX( playerSprite->getStateXSpeed() );
  playerSprite->movePosXWithSpeed();
  playerSprite->getHandlerAnimation()->animate();
  playerSprite->setPlayerMoveInY(false);
  stop();
}

void MeerkatP2::run()
{
  playerSprite->movePosXWithSpeed();
  playerSprite->getHandlerAnimation()->animate();
  playerSprite->setPlayerMoveInY(false);
  stop();
}

void MeerkatP2::jump()
{
  playerSprite->setPlayerMoveInY(true);
  playerSprite->setSpeedX( playerSprite->getPreviousStateXSpeed() );
  playerSprite->movePosXWithSpeed();
  playerSprite->movePosYWithSpeed();
  playerSprite->getHandlerAnimation()->animate();
  stop();
}

void MeerkatP2::fastAttack()
{
  playerSprite->setPlayerMoveInY(true);
  playerSprite->setSpeedX( playerSprite->getPreviousStateXSpeed() );
  playerSprite->movePosXWithSpeed();
  playerSprite->movePosYWithSpeed();

  if ( playerSprite->getHandlerAnimation()->getAnimationAlreadyEnd() )
  {
    returnToPreviousState();
  }
  else
  {
    playerSprite->getHandlerAnimation()->animate(); 
  }
}

void MeerkatP2::falling()
{
  playerSprite->setPlayerMoveInY(true);
  playerSprite->setSpeedX( playerSprite->getPreviousStateXSpeed() );
  playerSprite->movePosXWithSpeed();
  playerSprite->movePosYWithSpeed();
  playerSprite->getHandlerAnimation()->animate();

  if ( !isFalling() )
  {
    stop();
  }
}

void MeerkatP2::stopping()
{
  playerSprite->setPlayerMoveInY(false);
  playerSprite->movePosXWithSpeed();
  playerSprite->getHandlerAnimation()->animate();

  if ( playerSprite->getSpeedX() == 0.0f )
  {
	playerSprite->setPlayerMoveInX(false);
  }
  stop();
}

void MeerkatP2::draw()
{
  playerSprite->drawTexture();
}