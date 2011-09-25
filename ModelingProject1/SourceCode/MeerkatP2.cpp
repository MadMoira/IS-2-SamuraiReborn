
#include "MeerkatP2.h"

MeerkatP2::~MeerkatP2()
{
}

void MeerkatP2::initializePlayer(IDSprites id, std::string filename, std::vector<GLfloat> speedX, GLfloat speedY, GLfloat posX,
				GLfloat posY, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				IDSpriteStates state, GLfloat widthSprite, GLfloat heightSprite)
{
	playerSprite = new Sprite(id, filename, speedX, speedY, posX, posY, initialFrame, maxFrame, returnFrame,
							 state, widthSprite, heightSprite);
	keyboardHandler = new KeyboardHandler("merkaat.kes");

}

void MeerkatP2::still()
{
	
	playerSprite->movePosYWithSpeed();
	playerSprite->setSpeedX(0);
	stop();
			
}

void MeerkatP2::walk()
{
	playerSprite->setSpeedX(playerSprite->getStateXSpeed());
	if ( playerSprite->movePosXWithSpeed() )
	{
		playerSprite->getHandlerAnimation()->animate();
		return;
	}

	stop();
}

void MeerkatP2::run()
{
	playerSprite->setSpeedX(playerSprite->getStateXSpeed());
	if ( playerSprite->movePosXWithSpeed() )
	{
		playerSprite->getHandlerAnimation()->animate() ;
		return;
	}

	stop();
}

void MeerkatP2::jump(){
	
	if ( playerSprite->movePosXWithSpeed()&&playerSprite->movePosYWithSpeed() )
	{
		playerSprite->getHandlerAnimation()->animate() ;
	
		return;
	}
	

	stop();
}

void MeerkatP2::draw()
{
	playerSprite->drawTexture();
}