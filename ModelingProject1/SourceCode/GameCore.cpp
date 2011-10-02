
#include "GameCore.h"

GameCore::GameCore(void)
{
    configuration = new GameConfiguration();
    saves = new GameSaves();
    screen = new GameScreen();
    timer = new GameTimer();
	sound = new GameSound();
	camera = new Camera();
	isRunning = true;
}

GameCore::~GameCore(void)
{
    delete configuration;
    delete saves;
    delete screen;
    delete timer;
	delete sound;
	delete camera;
	playersList.clear();
}

bool GameCore::initializeGameCore()
{	
	sound->initSound();
	
	if( screen->initializeScreen())
	{
		camera->initCamera();
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

void GameCore::addPlayerToGame(Player *player, IDSprites id, std::string filename, std::vector<GLfloat> speedX, GLfloat speedY, GLfloat posX,
				GLfloat posY, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				IDSpriteStates state, GLfloat widthSprite, GLfloat heightSprite)
{
	playersList.push_back( player );
	playersList.at(id).initializePlayer(id, filename, speedX, speedY, 
										posX, posY, initialFrame, maxFrame, returnFrame, state,
										widthSprite, heightSprite);
}




