
#include "GameRender.h"
#include "Layer.h"

Layer::Layer(std::string name, GLfloat widthLayer, GLfloat heightLayer, Vector2f vel, 
		  GLfloat constantX, bool hasRepetition)
{
	nameLayer = name;
	widthLevelLayer = widthLayer;
	heightLevelLayer = heightLayer;
	texture = GameRender::loadTexture(name);
	speed.x = vel.x;
	speed.y = vel.y;
	offset.x = offset.y = 0.0f;
	repeat = hasRepetition;
	constantVelX = constantX;
}

Layer::~Layer(void)
{
	glDeleteTextures(1, &texture);
}

void Layer::drawLayerTexture(GLfloat widthScreen, GLfloat heightScreen)
{
	GameRender::drawLayerTexture(texture, offset, widthScreen, heightScreen);
}

void Layer::scrollLayer()
{
	offset.x += speed.x;
	offset.y += speed.y;

	checkScreenBoundaries();
}

bool Layer::checkScreenBoundaries()
{
	if (offset.x <= 0)
	{
		offset.x = 0;
		return false;
	}

	if (offset.x > widthLevelLayer - 1280.f)
	{
		if ( repeat )
		{
			return false;
		}

		offset.x = widthLevelLayer - 1280.f; 
		return true;
	}

	return false;
}

