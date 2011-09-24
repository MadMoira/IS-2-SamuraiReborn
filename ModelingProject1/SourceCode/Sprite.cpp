
#include "Sprite.h"

Sprite::Sprite(IDSprites id, std::string filename, std::vector<GLfloat> speedX, GLfloat speedY, GLfloat posX, GLfloat posY, 
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
	speedXVector = speedX;
	currentXSpeed=0;
	this->speedY = speedY;
	currentState = state;
	delayX=0;
	delayY=0;
}

Sprite::~Sprite(void)
{
	glDeleteTextures(1, &texture);
	maxFramesPerAnimation.clear();
	returnFramesPerAnimation.clear();
	speedXVector.clear();
}

bool Sprite::movePosXWithSpeed()
{
	bool movX=false, movY=false;
	if ( posX + getSpeedX() + width < 1280.f)
	{
		posX += getSpeedX();
		movX=true;
	}
	if(posY + getSpeedY()+height < 720.f){
		posY += getSpeedY();
		movY=true;
	}

	return movX&&movY;
}


void Sprite::setConstantSpeedX(int constant)
{
	for(std::string::size_type i = 0; i < speedXVector.size(); i++)
	{
		speedXVector.at(i) *= constant;
	}
	currentXSpeed*=constant;
}

void Sprite::changeCurrentFrame(int frame)
{
	handlerAnimation->setCurrentFrame(frame);
}

void Sprite::setCurrentState(IDSpriteStates state)
{
	 
	if ( currentState != state )
	{
		if(state == JUMPING){this->setSpeedY(-10.f);}
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
									handlerAnimation->getAnimationDirection(), currentState );
}




