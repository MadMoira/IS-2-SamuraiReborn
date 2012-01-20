#include "LoadingScreen.h"


LoadingScreen::LoadingScreen(void)
{
	statusBarWidth = 614;
	statusBarPosition = Vector2f(333.f,468.f);
	statusBarOffset = Vector2f(19.f,46.f);
	statusBarUnit = GameRender::loadTexture("Resources/Menus/Loading State/LoadingBar.png");
	background = GameRender::loadTexture("Resources/Menus/Loading State/LoadingState.png");
}


LoadingScreen::~LoadingScreen(void)
{
	 glDeleteTextures(1, &background);
}

void LoadingScreen::updateValues(int percentage){
	renderScreen(percentage);
}

void LoadingScreen::renderScreen(int percentage){
	glClear( GL_COLOR_BUFFER_BIT );

	GameRender::drawFullTexture(background,Vector2f(0,0),1280.f,720.f);
	GameRender::drawFullTexture(statusBarUnit,statusBarPosition,statusBarWidth*percentage/100,statusBarOffset.y);
	
	SDL_GL_SwapBuffers();
	if(percentage==100){
		Uint32 startTime = SDL_GetTicks();
		while(SDL_GetTicks()-startTime< 500){
		}
	}
}