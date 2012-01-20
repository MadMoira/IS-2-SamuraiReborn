#pragma once
#include <windows.h>
#include <gl\GL.h>
#include <SDL/SDL.h>
#include "Vector.h"
#include "GameRender.h"

class LoadingScreen
{
public:
	LoadingScreen(void);

	void updateValues(int percentage);
	void renderScreen(int percentage);

	~LoadingScreen(void);
private:
	int statusBarWidth;
	GLuint statusBarUnit;
	GLuint background;
	Vector2f statusBarPosition;
	Vector2f statusBarOffset;
};

