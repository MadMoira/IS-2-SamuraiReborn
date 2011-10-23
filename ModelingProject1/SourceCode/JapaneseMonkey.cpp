#include "JapaneseMonkey.h"


void JapaneseMonkey::initializeEnemy(IDSprites id, std::string filename, std::vector< Vector2f > speed,  
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite)
{
  enemySprite = new Sprite(id, filename, speed, pos, initialFrame, maxFrame, returnFrame,
							widthSprite, heightSprite);
}

void JapaneseMonkey::noAction()
{
  enemySprite->setSpeedX(0);
  stop();		
}

void JapaneseMonkey::walk()
{
  enemySprite->setSpeedX( enemySprite->getStateXSpeed() );
  if ( enemySprite->movePosXWithSpeed() )
  {
    enemySprite->getHandlerAnimation()->animate() ;
    return;
  }

  stop();
}

void JapaneseMonkey::run()
{
  enemySprite->setSpeedX( enemySprite->getStateXSpeed() );
  if ( enemySprite->movePosXWithSpeed() )
  {
    enemySprite->getHandlerAnimation()->animate() ;
    return;
  }

  stop();
}

void JapaneseMonkey::jump()
{
  enemySprite->setSpeedX( enemySprite->getPreviousStateXSpeed() );
  if ( enemySprite->movePosXWithSpeed() && enemySprite->movePosYWithSpeed() )
  {
    enemySprite->getHandlerAnimation()->animate() ;
    return;
  }

  stop();
}

void JapaneseMonkey::attack()
{
  enemySprite->setSpeedX( enemySprite->getStateXSpeed() );
  if ( enemySprite->movePosXWithSpeed() && enemySprite->getHandlerAnimation()->getCurrentFrame()+1 < 8 )
  {
    enemySprite->getHandlerAnimation()->animate() ;
    return;
  }

  returnToPreviousState();
}

void JapaneseMonkey::draw()
{
  enemySprite->drawTexture();
}

JapaneseMonkey::~JapaneseMonkey()
{
	delete enemySprite;
}