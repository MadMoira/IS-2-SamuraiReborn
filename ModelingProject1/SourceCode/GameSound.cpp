#include "GameSound.h"

GameSound::GameSound(void)
{
	result = FMOD::System_Create(&system);
	printf("FMOD created");
	ERRCHECK(result);

	//init sounds
	static std::string runningSound = "Running.mp3";
	static std::string fallingSound = "groundHit.mp3";
	static std::string meerkatAttackSound = "Sword (2).mp3";
	static std::string monkeySound = "Monkeys.mp3";
	Sounds.push_back(&runningSound);
	Sounds.push_back(&fallingSound);
	Sounds.push_back(&meerkatAttackSound);
	Sounds.push_back(&monkeySound);
}

bool GameSound::instanceFlag = false;
GameSound* GameSound::gameSound = NULL;

GameSound* GameSound::getInstance()
{
  if( !instanceFlag )
  {
    gameSound = new GameSound();
    gameSound->initSound();
    instanceFlag = true;
  }
  return gameSound;
}

GameSound::~GameSound()
{
}

void GameSound::closeAll()
{
	result = system->close();
	ERRCHECK(result);
	result = system->release();
	ERRCHECK(result);
}

bool GameSound::initSound()
{
	result = system->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}

void GameSound::loadSound(std::string name)
{
	const char* MusicName = name.c_str();
	printf("Loading");
	result = system->createStream(MusicName, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
	ERRCHECK(result);
	printf("PLaying");
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel[0]);
	ERRCHECK(result);	
}

//
void GameSound::PlaySound(int i)
{   
	std::string name = Sounds.at(i);
    currentSound = name.c_str();
	result = system->createStream( currentSound, FMOD_DEFAULT, 0, &sound );
	ERRCHECK(result);
	result = system->playSound( FMOD_CHANNEL_REUSE, sound, false, &channel[2]);
	ERRCHECK(result);
}

void GameSound::closeSound(){
	channel[2]->setVolume( 0.0 );
	currentSound = "NULL";
	}
//

void GameSound::stateSoundsHandling(GameCoreStates::SpriteState previousState){
	 if(previousState == GameCoreStates::RUNNING){
	  GameSound::getInstance()->closeSound();
  }
  if(previousState == GameCoreStates::FALLING){
	  GameSound::getInstance()->loadChunk(Sounds.at(1));
  }
}
//

void GameSound::loadChunk(std::string name)
{
	const char* ChunkName = name.c_str();
	result = system->createSound(ChunkName, FMOD_LOOP_OFF, 0, &chunks[0]);
	ERRCHECK(result);
	result = system->playSound(FMOD_CHANNEL_FREE, chunks[0], false, &channel[1]);
	ERRCHECK(result);
	result = channel[1]->setVolume(0.1f);
}

void GameSound::ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

void GameSound::upVolumeSE()
{
	float volume;
	channel[1]->getVolume(&volume);
	volume += 0.1f;
	result = channel[1]->setVolume(volume);
}

void GameSound::downVolumeSE()
{
	float volume;
	channel[1]->getVolume(&volume);
	volume -= 0.1f;
	result = channel[1]->setVolume(volume);
}

void GameSound::upVolumeMUS()
{
	float volume;
	channel[0]->getVolume(&volume);
	volume += 0.1f;
	result = channel[0]->setVolume(volume);
}

void GameSound::downVolumeMUS()
{
	float volume;
	channel[0]->getVolume(&volume);
	volume -= 0.1f;
	result = channel[0]->setVolume(volume);
}