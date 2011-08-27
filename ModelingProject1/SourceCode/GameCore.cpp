#include "GameCore.h"
#include <string>
#include "SDL_image.h"

GameCore::GameCore(void)
{
	currentGameState = 0;
	configuration = new GameConfiguration();
	saves = new GameSaves();
	screen = new GameScreen();
	timer = new GameTimer();
	currentStateID = STATE_NULL;
}

bool GameCore::initGame(){
	if(screen->initialize()){
		return true;
	}
	return false;
}

GameCore::~GameCore(void)
{
	delete currentGameState;
	delete configuration;
	delete saves;
	delete screen;
	delete timer;
}

GLuint loadTexture(std::string name){
	
	SDL_Surface* image = load_image(name);
	
	GLuint texture;

	if(image!=NULL){
		
		glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(	GL_TEXTURE_2D,
						0, 
						4, 
						image->w, 
						image->h,
						0, 
						GL_BGRA,
						GL_UNSIGNED_BYTE, 
						image->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		SDL_FreeSurface(image);
		return texture;
	}
}
