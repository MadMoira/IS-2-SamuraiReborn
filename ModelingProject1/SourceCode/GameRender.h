#pragma once

#include <windows.h>
#include <string>
#include <GL/gl.h>

#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

#include "Vector.h"

class GameRender
{
public:
	GameRender(void);
	~GameRender(void);

	static GLuint loadTexture(std::string name);
	void drawFullTexture(GLuint texture, Vector2f pos, GLfloat widthTexture, GLfloat heightTexture);
	static void drawSpriteTexture(GLuint texture, Vector2f pos, int currentFrame, 
									GLfloat widthTexture, GLfloat heightTexture, GLfloat widthSprite, GLfloat heightSprite,
									int direction, int state);
	static void drawLayerTexture(GLuint texture, Vector2f offset, GLfloat widthScreen, 
								GLfloat heightScreen);
};

