
#include "Sprite.h"

#include "GameRender.h"

Sprite::Sprite(IDSprites id, std::string filename, GLfloat speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
				int initialFrame, int maxFrame, GLfloat widthSprite, GLfloat heightSprite)
{
	texture = GameRender::loadTexture(filename);
	glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &this->widthTexture);
	glGetTexLevelParameterfv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &this->heightTexture);

	width = widthSprite;	height = heightSprite;
	this->posX = posX;  this->posY = posY;
	this->speedX = speedX;	this->speedY = speedY;
	currentFrame = initialFrame;
	maxFrameFromCurrentState = maxFrame;
	currentState = STILL;
}

Sprite::~Sprite(void)
{
	glDeleteTextures(1, &texture);
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

void Sprite::setCurrentState(int state)
{
	if ( currentState != state )
	{
		currentState = state;
	}

	return;
}

void Sprite::updateCurrentSpriteFrame()
{
	if ( currentFrame + 1 > maxFrameFromCurrentState )
	{
		currentFrame = 1;
	}

	else
	{
		currentFrame += 1;
	}
}

void Sprite::drawTexture()
{
	GameRender::drawSpriteTexture(texture, posX, posY, currentFrame, widthTexture, heightTexture, width, height);
}


