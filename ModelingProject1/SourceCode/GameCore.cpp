#include "GameCore.h"

using namespace std;
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
