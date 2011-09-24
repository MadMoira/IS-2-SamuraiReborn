#pragma once

#include <windows.h>
#include <GL/gl.h>

#include <vector>
#include <string>

class Layer
{
public:
	Layer(std::string name, GLfloat widthLayer, GLfloat heightLayer, GLfloat velX, GLfloat velY);
	~Layer(void);

	void drawLayerTexture(GLfloat widthScreen, GLfloat heightScreen);
	
	GLuint getTexture() { return texture; }
	void setLayerTexture(GLuint layerTexture) { texture = layerTexture; }

	GLfloat getWidthLevelLayer() { return widthLevelLayer; }
	void setWidthLevelLayer(GLfloat width) { widthLevelLayer = width; }

	GLfloat getHeightLevelLayer() { return heightLevelLayer; }
	void setHeightLevelLayer(GLfloat height) { heightLevelLayer = height; }

	GLfloat setVelocityX(GLfloat velX) { velocityX = velX; }

	bool scrollLayer();

	GLfloat getOffsetX() { return offsetX; }
	void setOffsetX(GLfloat velX) { offsetX = velX; }

	GLfloat getOffsetY() { return offsetY; }

	bool checkScreenBoundaries();

private:
	std::string nameLayer;
	GLuint texture;
	GLfloat widthLevelLayer, heightLevelLayer;
	GLfloat velocityX, velocityY, offsetX, offsetY;
};

