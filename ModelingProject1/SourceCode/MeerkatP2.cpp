
#include "MeerkatP2.h"

Characters::MeerkatP2::~MeerkatP2()
{
  delete characterSprite;
  delete inputMapper;
  delete stats;
  delete score;
}

void Characters::MeerkatP2::initializeCharacter(SpriteData::IDSprites id, std::string filename, std::vector< Vector2f > speed,
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
                std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
                std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  characterSprite = new PlayerSprite(id, filename, speed, pos, initialFrame, maxFrame, returnFrame,
                            widthSprite, heightSprite, framerateAnimations, delayMovement);

  stats = new PlayerStats::Stats();
  score = new PlayerScore::Score();

  inputMapper = new InputMapping::GameInputMapper();
  inputMapper->pushContext("maincontext");
  inputMapper->addCallback( Player::inputCallback, 0);
}

void Characters::MeerkatP2::noAction()
{
  characterSprite->setSpeedX(0.0f);
  characterSprite->setPlayerMoveInX(false);
  characterSprite->setPlayerMoveInY(false);
  characterSprite->setPlayerMoveInXCurrentFrame(false);
  stop();	
}

void Characters::MeerkatP2::walk()
{
  characterSprite->setSpeedX( characterSprite->getStateXSpeed() );
  characterSprite->movePosXWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  characterSprite->setPlayerMoveInY(false);
  stop();
}

void Characters::MeerkatP2::run()
{
  characterSprite->movePosXWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  characterSprite->setPlayerMoveInY(false);
  stop();
}

void Characters::MeerkatP2::jump()
{
  characterSprite->setPlayerMoveInY(true);
  characterSprite->setSpeedX( characterSprite->getPreviousStateXSpeed() );
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  stop();
}

void Characters::MeerkatP2::fastAttack()
{
  characterSprite->setPlayerMoveInY(true);
  characterSprite->setSpeedX( characterSprite->getPreviousStateXSpeed() );
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();

  if ( characterSprite->getHandlerAnimation()->getAnimationAlreadyEnd() )
  {
    returnToPreviousState();
  }
  else
  {
    characterSprite->getHandlerAnimation()->animate(); 
  }
}

void Characters::MeerkatP2::falling()
{
  characterSprite->setPlayerMoveInY(true);
  characterSprite->setSpeedX( characterSprite->getPreviousStateXSpeed() );
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();
  characterSprite->getHandlerAnimation()->animate();

  if ( !isFalling() )
  {
    stop();
  }
}

void Characters::MeerkatP2::stopping()
{
  characterSprite->setPlayerMoveInY(false);
  characterSprite->movePosXWithSpeed();
  characterSprite->getHandlerAnimation()->animate();

  if ( characterSprite->getSpeedX() == 0.0f )
  {
    characterSprite->setPlayerMoveInX(false);
  }
  stop();
}

void Characters::MeerkatP2::draw()
{
  characterSprite->drawTexture();
}