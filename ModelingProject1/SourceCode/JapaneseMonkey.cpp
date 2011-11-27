
#include "JapaneseMonkey.h"

void Characters::JapaneseMonkey::initializeCharacter(SpriteData::IDSprites id, std::string filename, std::vector< Vector2f > speed, 
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
                std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
                std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  characterSprite = new EnemySprite(id, filename, speed, pos, initialFrame, maxFrame, returnFrame,
                           widthSprite, heightSprite,framerateAnimations,delayMovement);
}

void Characters::JapaneseMonkey::noAction()
{
  /*enemySprite->setSpeedX(0);
  enemySprite->setPlayerMoveInX(false);
  enemySprite->setPlayerMoveInY(false);
  stop();	*/	
}

void Characters::JapaneseMonkey::walk()
{
  /*enemySprite->setSpeedX( enemySprite->getStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->getHandlerAnimation()->animate() ;
  stop();*/
}

void Characters::JapaneseMonkey::run()
{
  /*enemySprite->setSpeedX( enemySprite->getStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->getHandlerAnimation()->animate();
  stop();*/
}

void Characters::JapaneseMonkey::jump()
{
  /*enemySprite->setPlayerMoveInY(true);
  enemySprite->setSpeedX( enemySprite->getPreviousStateXSpeed() );
  enemySprite->movePosXWithSpeed();
  enemySprite->movePosYWithSpeed();
  enemySprite->getHandlerAnimation()->animate() ;
  stop();*/
}

void Characters::JapaneseMonkey::attack()
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

void Characters::JapaneseMonkey::draw()
{
  characterSprite->drawTexture();
}