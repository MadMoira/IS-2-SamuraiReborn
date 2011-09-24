
#include "Sprite.h"

Sprite::Sprite(IDSprites id, std::string filename, GLfloat speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
				int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, IDSpriteStates state,
				GLfloat widthSprite, GLfloat heightSprite)
{
	texture = GameRender::loadTexture(filename);
	glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &this->widthTexture);
	glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &this->heightTexture);

	handlerAnimation = new Animation(initialFrame, maxFrame.at(state), returnFrame.at(state), RIGHT );

	maxFramesPerAnimation = maxFrame;
	returnFramesPerAnimation = returnFrame;

	width = widthSprite;	height = heightSprite;
	this->posX = posX;  this->posY = posY;
	this->speedX = speedX;	this->speedY = speedY;
	currentState = state;
}

Sprite::~Sprite(void)
{
	glDeleteTextures(1, &texture);
	maxFramesPerAnimation.clear();
	returnFramesPerAnimation.clear();
}

bool Sprite::movePosXWithSpeed()
{
	if ( posX + speedX + width < 1280.f)
	{
		posX += speedX;
		return true;
	}

	return false;
}

void Sprite::changeCurrentFrame(int frame)
{
	handlerAnimation->setCurrentFrame(frame);
}

void Sprite::setCurrentState(IDSpriteStates state)
{
	if ( currentState != state )
	{
		currentState = state;

		handlerAnimation->setMaxFrame( maxFramesPerAnimation.at(currentState) );
		handlerAnimation->setReturnFrame( returnFramesPerAnimation.at(currentState) );
	}

	return;
}

void Sprite::drawTexture()
{
	GameRender::drawSpriteTexture(texture, posX, posY,  handlerAnimation->getCurrentFrame(), 
									widthTexture, heightTexture, width, height, 
									handlerAnimation->getAnimationDirection() );
}




