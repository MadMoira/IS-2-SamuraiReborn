
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

void GameCore::addPlayerToGame(Player *player, IDSprites id, std::string filename, std::vector< Vector2f> speed, 
				GLfloat speedY, Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, IDSpriteStates state, GLfloat widthSprite, GLfloat heightSprite)
{
	playersList.push_back( player );
	playersList.at(id).initializePlayer(id, filename, speed, speedY, 
										pos, initialFrame, maxFrame, returnFrame, state,
										widthSprite, heightSprite);
}



