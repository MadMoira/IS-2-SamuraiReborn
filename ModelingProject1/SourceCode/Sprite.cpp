
#include "Sprite.h"

Sprite::Sprite(IDSprites id, std::string filename, std::vector< Vector2f > speed, GLfloat speedY, Vector2f pos, 
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
	position.x = pos.x;		position.y = pos.y;
	this->speed = speed;
	currentXSpeed = 0;
	this->speedY = speedY;
	currentState = state;
	delay.x = 0;
	delay.y = 0;
}

Sprite::~Sprite(void)
{
	glDeleteTextures(1, &texture);
	maxFramesPerAnimation.clear();
	returnFramesPerAnimation.clear();
	speed.clear();
}

bool Sprite::movePosXWithSpeed()
{
	bool movX=false;
	if ( position.x + getSpeedX() + width < 1280.f )
	{
		position.x += getSpeedX();
		movX=true;
	}

	return movX;
}

bool Sprite::movePosYWithSpeed()
{
	bool movY=false;
	if(position.y + getSpeedY()+height < 650.f){
		position.y += getSpeedY();
		movY=true;
	}
	return movY;
}

void Sprite::setConstantSpeedX(int constant)
{
	for(std::string::size_type i = 0; i < speed.size(); i++)
	{
		speed.at(i).x *= constant;
	}

	currentXSpeed *= constant;
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
	GameRender::drawSpriteTexture(texture, position,  handlerAnimation->getCurrentFrame(), 
									widthTexture, heightTexture, width, height, 
									handlerAnimation->getAnimationDirection(), currentState );
}




