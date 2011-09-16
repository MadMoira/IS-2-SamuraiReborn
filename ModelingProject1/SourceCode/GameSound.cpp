#include "GameSound.h"

GameSound::GameSound(void)
{
	result = FMOD::System_Create(&system);
	ERRCHECK(result);
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
	result = system->createStream(MusicName, /*FMOD_HARDWARE |*/ FMOD_LOOP_NORMAL/* | FMOD_2D*/, 0, &sound);
	ERRCHECK(result);
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel[0]);
	ERRCHECK(result);	
}

void GameSound::loadChunk(std::string name)
{
	const char* ChunkName = name.c_str();
	result = system->createSound(ChunkName, FMOD_LOOP_OFF, 0, &chunks[0]);
	ERRCHECK(result);
	result = system->playSound(FMOD_CHANNEL_FREE, chunks[0], false, &channel[1]);
	ERRCHECK(result);
	result = channel[1]->setVolume(0.1);
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