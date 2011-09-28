
#include "GameRender.h"
#include "Layer.h"

Layer::Layer(std::string name, GLfloat widthLayer, GLfloat heightLayer, GLfloat velX, GLfloat velY, 
			GLfloat constantX, bool hasRepetition)
{
	nameLayer = name;
	widthLevelLayer = widthLayer;
	heightLevelLayer = heightLayer;
	texture = GameRender::loadTexture(name);
	velocityX = velX;
	velocityY = velY;
	offsetX = offsetY = 0.0f;
	repeat = hasRepetition;
	constantVelX = constantX;
}

Layer::~Layer(void)
{
	glDeleteTextures(1, &texture);
}

void Layer::drawLayerTexture(GLfloat widthScreen, GLfloat heightScreen)
{
	GameRender::drawLayerTexture(texture, offsetX, offsetY, widthScreen, heightScreen);
}

void Layer::scrollLayer()
{
	offsetX += velocityX;
	offsetY += velocityY;

	//checkScreenBoundaries();
}

bool Layer::checkScreenBoundaries()
{
	if (offsetX <= 0)
	{
		offsetX = 0;
		return false;
	}

	if (offsetX > widthLevelLayer - 1280.f)
	{
		if ( repeat )
		{
			return false;
		}

		offsetX = widthLevelLayer - 1280.f; 
		return true;
	}

	return false;
}

