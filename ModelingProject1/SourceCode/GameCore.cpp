#include "GameCore.h"

GameCore::GameCore(void)
{
    configuration = new GameConfiguration();
    saves = new GameSaves();
    screen = new GameScreen();
    timer = new GameTimer();
	sound = new GameSound();
	isRunning = true;
}

GameCore::~GameCore(void)
{
    delete configuration;
    delete saves;
    delete screen;
    delete timer;
	delete sound;
	playersList.clear();
}

bool GameCore::initializeGameCore()
{	
	sound->initSound();

	if( screen->initializeScreen())
	{
		return true;
    }
	
	return false;
}

bool GameCore::cleanUpGameCore()
{
	sound->closeAll();
	SDL_Quit();

	return true;
}

void GameCore::startTimer()
{
	timer->start();
}

void GameCore::startMusic(std::string filename)
{
	sound->loadSound(filename);	
}

void GameCore::startSoundEffect(std::string filename)
{
	sound->loadChunk(filename);
}

void GameCore::addPlayerToGame(Player *player)
{
	playersList.push_back( player );
	playersList.at(0).initializePlayer(PANDA, "Panda - SpriteSheet.png", 10.0f, 0.0f, 200.0f, 200.0f, 250.f, 187.f, 0, 8);
}



