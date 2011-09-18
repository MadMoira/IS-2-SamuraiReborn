
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
	keyboardHandler = new KeyboardHandler(SDLK_d, SDLK_a, SDLK_c);
}

void MeerkatP2::walk()
{
	if ( playerSprite->movePosXWithSpeed() )
	{
		playerSprite->getHandlerAnimation()->animate();
		return;
	}

	playerSprite->setCurrentState(STILL);
	playerSprite->changeCurrentFrame(STILL);
}

void MeerkatP2::run()
{
	if ( playerSprite->movePosXWithSpeed() )
	{
		playerSprite->getHandlerAnimation()->animate() ;
		return;
	}

	playerSprite->setCurrentState(STILL);
	playerSprite->changeCurrentFrame(STILL);
}

void MeerkatP2::draw()
{
	playerSprite->drawTexture();
}