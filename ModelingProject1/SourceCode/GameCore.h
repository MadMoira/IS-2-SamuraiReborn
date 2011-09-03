#pragma once

#include <string>

#include "GameState.h"
#include "GameConfiguration.h"
#include "GameSaves.h"
#include "GameScreen.h"
#include "GameTimer.h"

class GameCore
{
public:
	GameCore();
	~GameCore(void);

	void changeState();
	void close();
	bool initGame();
	void initPlayers();
	void setNewState();
	void setup();

	SDL_Surface *load_image(std::string filename);
    GLuint loadTexture(std::string name);

	void setupFPS();

	
private:
	GameState *currentGameState;
	GameConfiguration *configuration;
	GameSaves *saves;
	GameScreen *screen;
	GameTimer *timer;
	int currentStateID;
};

