
#include "PandaP1.h"

PandaP1::~PandaP1()
{
	delete playerSprite;
	delete keyboardHandler;
}

void PandaP1::initializePlayer(IDSprites id, std::string filename, GLfloat speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, IDSpriteStates state,
				GLfloat widthSprite, GLfloat heightSprite)
{
	playerSprite = new Sprite(id, filename, speedX, speedY, posX, posY, initialFrame, maxFrame, returnFrame,
							 state, widthSprite, heightSprite);
	keyboardHandler = new KeyboardHandler(SDLK_RIGHT, SDLK_LEFT);
}

void PandaP1::walk()
{
	if ( playerSprite->movePosXWithSpeed() )
	{
		playerSprite->getHandlerAnimation()->animate() ;
		return;
	}

	playerSprite->setCurrentState(STILL);
	playerSprite->changeCurrentFrame(INITIAL_POSITION);
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