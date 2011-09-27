
#include "PandaP1.h"

PandaP1::~PandaP1()
{
	delete playerSprite;
	delete keyboardHandler;
}

void PandaP1::initializePlayer(IDSprites id, std::string filename, std::vector<GLfloat> speedX, GLfloat speedY, GLfloat posX,
				GLfloat posY, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				IDSpriteStates state, GLfloat widthSprite, GLfloat heightSprite)
{
	playerSprite = new Sprite(id, filename, speedX, speedY, posX, posY, initialFrame, maxFrame, returnFrame,
							 state, widthSprite, heightSprite);
	keyboardHandler = new KeyboardHandler("panda.kes");
}

void PandaP1::noAction()
{
	
	playerSprite->movePosYWithSpeed();
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
	if ( playerSprite->movePosXWithSpeed()&&playerSprite->movePosYWithSpeed() )
	{
		playerSprite->getHandlerAnimation()->animate() ;
	
		return;
	}
	
	stop();
}

void PandaP1::draw()
{
	playerSprite->drawTexture();
}