
#include "GameCore.h"
#include "Layer.h"

Layer::Layer(std::string name, GLfloat widthLayer, GLfloat heightLayer, GLfloat velX, GLfloat velY)
{
	nameLayer = name;
	widthLevelLayer = widthLayer;
	heightLevelLayer = heightLayer;
	texture = GameCore::loadTexture(name);
	velocityX = velX;
	velocityY = velY;
	offsetX = offsetY = 0.0f;
}

Layer::~Layer(void)
{
	glDeleteTextures(1, &texture);
}

void Layer::drawLayerTexture(GLfloat widthScreen, GLfloat heightScreen)
{
	GLfloat widthTexture, heightTexture;
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );	
	
	glBindTexture( GL_TEXTURE_2D, texture );

	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &widthTexture);
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &heightTexture);

	widthTexture = 1600.f;
		heightTexture = 720.f;

	const GLfloat vertX = 0.0f;
	const GLfloat vertY = 0.0f;
	
	const GLfloat verts[] = {
			vertX, vertY,
			vertX + widthScreen, vertY,
			vertX + widthScreen, vertY + heightScreen,
			vertX, vertY + heightScreen
	};

	const GLfloat textureX = offsetX/widthScreen;
	const GLfloat textureY = 0.0f;
	const GLfloat textureWidth = (widthScreen + offsetX) / widthTexture;
	const GLfloat textureHeight = (heightScreen + offsetY) / heightTexture;

	const GLfloat texVerts[] = {
			textureX, textureY,
			textureWidth, textureY,
			textureWidth, textureHeight,
			textureX, textureHeight
	};
			
	glVertexPointer(2, GL_FLOAT, 0, verts);
	glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState( GL_VERTEX_ARRAY );			
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );	

}

bool Layer::scrollLayer()
{
	offsetX += velocityX;
	offsetY += velocityY;

	return checkScreenBoundaries();
}

bool Layer::checkScreenBoundaries()
{
	if (offsetX > widthLevelLayer - 1280.f)
	{
		offsetX = widthLevelLayer - 1280.f; 
		return true;
	}

	return false;
}

