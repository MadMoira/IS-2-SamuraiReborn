
#include "JapaneseMonkey.h"

void JapaneseMonkey::initializeEnemy(SpriteData::IDSprites id, std::string filename, std::vector< Vector2f > speed, 
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
				std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  enemySprite = new Sprite(id, filename, speed, pos, initialFrame, maxFrame, returnFrame,
						   widthSprite, heightSprite,framerateAnimations,delayMovement);
}

void JapaneseMonkey::noAction()
{
  /*enemySprite->setSpeedX(0);
  enemySprite->setPlayerMoveInX(false);
  enemySprite->setPlayerMoveInY(false);
  stop();	*/	
}

void JapaneseMonkey::walk()
{
  /*enemySprite->setSpeedX( enemySprite->getStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->getHandlerAnimation()->animate() ;
  stop();*/
}

void JapaneseMonkey::run()
{
  /*enemySprite->setSpeedX( enemySprite->getStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->getHandlerAnimation()->animate();
  stop();*/
}

void JapaneseMonkey::jump()
{
  /*enemySprite->setPlayerMoveInY(true);
  enemySprite->setSpeedX( enemySprite->getPreviousStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->movePosYWithSpeed();
  enemySprite->getHandlerAnimation()->animate() ;
  stop();*/
}

void JapaneseMonkey::attack()
{
  /*enemySprite->setPlayerMoveInY(true);
  enemySprite->setSpeedX( enemySprite->getPreviousStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->movePosYWithSpeed();

  if ( enemySprite->getHandlerAnimation()->getAnimationAlreadyEnd() )
  {
    returnToPreviousState();
  }
  else
  {
    enemySprite->getHandlerAnimation()->animate(); 
  }*/
}

void JapaneseMonkey::draw()
{
  enemySprite->drawTexture();
}