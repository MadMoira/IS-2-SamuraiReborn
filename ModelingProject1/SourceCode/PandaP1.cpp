
#include "PandaP1.h"

PandaP1::~PandaP1()
{
	delete playerSprite;
}

void PandaP1::initializePlayer(IDSprites id, std::string filename, std::vector< Vector2f > speed,  
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite)
{
  playerSprite = new Sprite(id, filename, speed, pos, initialFrame, maxFrame, returnFrame,
							widthSprite, heightSprite);

  stats = new PlayerStats::Stats();

  inputMapper = new InputMapping::GameInputMapper();
  inputMapper->pushContext("maincontext");
  inputMapper->addCallback( Player::inputCallback, 0);
}

void PandaP1::noAction()
{
  playerSprite->setSpeedX(0);
  stop();		
}

void PandaP1::walk()
{
  playerSprite->setSpeedX(playerSprite->getStateXSpeed());
  if ( playerSprite->movePosXWithSpeed() )
  {
    playerSprite->getHandlerAnimation()->animate() ;
    return;
  }

  stop();
}

void PandaP1::run()
{
  playerSprite->setSpeedX(playerSprite->getStateXSpeed());
  if ( playerSprite->movePosXWithSpeed() )
  {
    playerSprite->getHandlerAnimation()->animate() ;
    return;
  }

  stop();
}

void PandaP1::jump()
{
  playerSprite->setSpeedX(playerSprite->getPreviousStateXSpeed());
  if ( playerSprite->movePosXWithSpeed() && playerSprite->movePosYWithSpeed() )
  {
    playerSprite->getHandlerAnimation()->animate() ;
    return;
  }

  stop();
}

void PandaP1::draw()
{
  playerSprite->drawTexture();
  stats->drawHealthBar();
  stats->drawHealth();
}