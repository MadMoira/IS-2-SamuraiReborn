#pragma once

#include <string>
#include "SDL/SDL_image.h"

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

    static GLuint loadTexture(std::string name);

	static void drawTexture(GLuint texture, GLfloat x, GLfloat y, GLfloat offx, GLfloat offy);

	void setupFPS();
	
private:
	GameState *currentGameState;
	GameConfiguration *configuration;
	GameSaves *saves;
	GameScreen *screen;
	GameTimer *timer;
	int currentStateID;
};

