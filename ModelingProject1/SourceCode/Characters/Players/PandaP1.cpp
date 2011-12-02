
#include "PandaP1.h"

Characters::PandaP1::~PandaP1()
{
  delete characterSprite;
  delete inputMapper;
  delete stats;
  delete score;
}

void Characters::PandaP1::initializeCharacter(SpriteData::IDSprites id, std::string filename, 
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
                std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
                std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  characterSprite = new PlayerSprite(id, filename, pos, initialFrame, maxFrame, returnFrame,
                            widthSprite, heightSprite, framerateAnimations, delayMovement);

  stats = new PlayerStats::Stats();
  score = new PlayerScore::Score();

  inputMapper = new InputMapping::GameInputMapper();
  inputMapper->pushContext("maincontext");
  inputMapper->addCallback( Player::inputCallback, 0);
}

void Characters::PandaP1::noAction()
{
  characterSprite->setPlayerMoveInX(false);
  characterSprite->setPlayerMoveInY(false);
  characterSprite->setPlayerMoveInXCurrentFrame(false);
  stop();		
}

void Characters::PandaP1::walk()
{
  characterSprite->movePosXWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  characterSprite->setPlayerMoveInY(false);
  stop();
}

void Characters::PandaP1::run()
{
  characterSprite->movePosXWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  characterSprite->setPlayerMoveInY(false);
  stop();
}

void Characters::PandaP1::jump()
{
  characterSprite->setPlayerMoveInY(true);
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();
  characterSprite->getHandlerAnimation()->animate();
  stop();
}

void Characters::PandaP1::fastAttack()
{
  characterSprite->setPlayerMoveInY(true);
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

void Characters::PandaP1::falling()
{
  characterSprite->setPlayerMoveInY(true);
  characterSprite->movePosXWithSpeed();
  characterSprite->movePosYWithSpeed();
  characterSprite->getHandlerAnimation()->animate();

  if ( !isFalling() )
  {
    stop();
  }
}

void Characters::PandaP1::draw()
{
  characterSprite->drawTexture();
}