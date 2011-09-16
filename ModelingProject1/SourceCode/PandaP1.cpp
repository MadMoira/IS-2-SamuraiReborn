#include "PandaP1.h"


PandaP1::~PandaP1()
{
	delete playerSprite;
	delete keyboardHandler;
}

void PandaP1::initializePlayer(IDSprites id, std::string filename, GLfloat speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
								GLfloat widthSprite, GLfloat heightSprite, int initialFrame, int maxFrame)
{
	playerSprite = new Sprite(id, filename, speedX, speedY, posX, posY, initialFrame, maxFrame, widthSprite, heightSprite);
	keyboardHandler = new KeyboardHandler();
}

void PandaP1::walk()
{
	if ( playerSprite->movePosXWithSpeed() )
	{
		playerSprite->updateCurrentSpriteFrame();
		return;
	}

	playerSprite->setCurrentState(STILL);
	playerSprite->setCurrentFrame(INITIAL_POSITION);
}

void PandaP1::draw()
{
	playerSprite->drawTexture();
}

void PandaP1::executeAction()
{
	switch( playerSprite->getCurrentState() )
	{
	case STILL:
		{
			break;
		}
	case WALKING:
		{
			walk();
			break;
		}
	}
}