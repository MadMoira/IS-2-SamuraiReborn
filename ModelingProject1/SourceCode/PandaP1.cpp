
#include "PandaP1.h"

PandaP1::~PandaP1()
{
  delete playerSprite;
  delete inputMapper;
  delete stats;
  delete score;
}

void PandaP1::initializePlayer(IDSprites id, std::string filename, std::vector< Vector2f > speed,  
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
				std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  playerSprite = new Sprite(id, filename, speed, pos, initialFrame, maxFrame, returnFrame,
							widthSprite, heightSprite, framerateAnimations, delayMovement);

  stats = new PlayerStats::Stats();
  score = new Score::PlayerScore();

  inputMapper = new InputMapping::GameInputMapper();
  inputMapper->pushContext("maincontext");
  inputMapper->addCallback( Player::inputCallback, 0);
}

void PandaP1::noAction()
{
  playerSprite->setSpeedX(0);
  playerSprite->setPlayerMoveInX(false);
  playerSprite->setPlayerMoveInY(false);
  stop();		
}

void PandaP1::walk()
{
  playerSprite->setSpeedX( playerSprite->getStateXSpeed() );
  playerSprite->movePosXWithSpeed();
  playerSprite->getHandlerAnimation()->animate();
  stop();
}

void PandaP1::run()
{
  playerSprite->setSpeedX( playerSprite->getStateXSpeed() );
  playerSprite->movePosXWithSpeed();
  playerSprite->getHandlerAnimation()->animate();
  stop();
}

void PandaP1::jump()
{
	if ( playerSprite->getPreviousState() == GameCoreStates::STILL &&
		playerSprite->getCurrentState() == GameCoreStates::JUMPING 
		&& playerSprite->getHandlerAnimation()->getCurrentFrame() == 1)
	{
		int d = 4;
	}

  playerSprite->setPlayerMoveInY(true);
  playerSprite->setSpeedX( playerSprite->getPreviousStateXSpeed() );
  playerSprite->movePosXWithSpeed();
  playerSprite->movePosYWithSpeed();
  playerSprite->getHandlerAnimation()->animate();
  stop();
}

void PandaP1::fastAttack()
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

void PandaP1::falling()
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

void PandaP1::draw()
{
  playerSprite->drawTexture();
}