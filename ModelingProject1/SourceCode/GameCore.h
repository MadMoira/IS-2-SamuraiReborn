#pragma once

#include <string>
#include "SDL/SDL_image.h"
#include "GameState.h"
#include "GameConfiguration.h"
#include "GameSaves.h"
#include "GameScreen.h"
#include "GameTimer.h"
#include "GameSound.h"
#include "PandaP1.h"

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
	void show(int, int, GLuint, int);
	void startMusic(std::string);
	void startSoundEffect(std::string);
	void startTimer();
	
	
    static GLuint loadTexture(std::string name);

	static void drawTexture_animation(int, int, GLuint);
	static void drawTexture(GLuint texture, GLfloat x, GLfloat y, GLfloat offx, GLfloat offy);

	void setupFPS();
	
private:
	GameState *currentGameState;
	GameConfiguration *configuration;
	GameSaves *saves;
	GameScreen *screen;
	GameTimer *timer;
	GameSound *sound;
	int currentStateID;
};

