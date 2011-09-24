#pragma once

#include <windows.h>
#include <string>
#include <GL/gl.h>

#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

class GameRender
{
public:
	GameRender(void);
	~GameRender(void);

	static GLuint loadTexture(std::string name);
	void drawFullTexture(GLuint texture, GLfloat x, GLfloat y, GLfloat widthTexture, GLfloat heightTexture);
	static void drawSpriteTexture(GLuint texture, GLfloat posX, GLfloat posY, int currentFrame, 
									GLfloat widthTexture, GLfloat heightTexture, GLfloat widthSprite, GLfloat heightSprite,
									int direction);
};

