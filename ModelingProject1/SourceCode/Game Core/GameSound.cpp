#include "GameSound.h"

GameSound::GameSound(void)
{
  result = FMOD::System_Create(&system);
  ERRCHECK(result);
  sFilename = "Game Core/Musics.txt";
  lFilename = "Game Core/LevelSounds.txt";
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
  ambienceSounds.clear();
  statesSounds.clear();
}

bool GameSound::initSound()
{
  result = system->init(32, FMOD_INIT_NORMAL, 0);
  return true;
}

void GameSound::closeSound()
{
  channel[2]->setVolume( 0.0 );
  currentSound = "NULL";
}

void GameSound::initSounds(int row, int soundType)
{
   std::string line;
   if( soundType == 0)
   {
     line = readLineFromFile(sFilename ,row);
   }
   else
   {
     line = readLineFromFile(lFilename ,row);
   }
   splitFileSounds(line, soundType);
}

void GameSound::splitFileSounds(std::string line, int soundType)
{
  std::string temp;

  for(std::string::size_type i = 0; i < line.size(); i++)
  {
    if( line.at(i) == ';' && temp != "" )
	{
      if( soundType == 0 )
	  {
        statesSounds.push_back(temp);
      }
	  else
	  {
        ambienceSounds.push_back(temp);
      }       
      temp = "";
    }
	else
	{
      temp += line.at(i);
    }
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

void GameSound::loadChunk(int row, int soundType, int soundID)
{
  initSounds(row, soundType);
  std::string name;

  if(soundType == 0)
  {
    name = statesSounds.at(soundID);
  }
  else
  {
    name = ambienceSounds.at(soundID);
  }
                
  if(name == "none")
  {
    return;
  }

  const char* chunkName = name.c_str();
  result = system->createSound(chunkName, FMOD_LOOP_OFF, 0, &chunks[0]);
  ERRCHECK(result);

  result = system->playSound(FMOD_CHANNEL_FREE, chunks[0], false, &channel[1]);
  ERRCHECK(result);
  result = channel[1]->setVolume(0.1f);
}

void GameSound::loadSound(int row, int soundType, int soundID)
{
  initSounds(row, soundType);
  std::string name;

  if(soundType == 0)
  {
    name = statesSounds.at(soundID);
  }
  else
  {
    name = ambienceSounds.at(soundID);
  }
                
  if(name == "none")
  {
    return;
  }
  
  const char* musicName = name.c_str();
  printf("Loading");
  result = system->createStream(musicName, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
  ERRCHECK(result);
        
  printf("Playing");
  result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel[0]);
  ERRCHECK(result);
}

void GameSound::playSound(int row, int soundType, int soundID)
{
  initSounds(row, soundType);
  std::string name;

  if(soundType == 0)
  {
    name = statesSounds.at(soundID);
  }
  else
  {
    name = ambienceSounds.at(soundID);
  }
                
  if( name == "none" )
  {
    return;
  }

  currentSound = name.c_str();
  result = system->createStream( currentSound, FMOD_DEFAULT, 0, &sound );
  ERRCHECK(result);
  
  result = system->playSound( FMOD_CHANNEL_REUSE, sound, false, &channel[2]);
  ERRCHECK(result);
}

void GameSound::stateSoundsHandling(GameCoreStates::SpriteState previousState)
{
  if( previousState == GameCoreStates::RUNNING )
  {
    GameSound::getInstance()->closeSound();
  }
  /*if(previousState == GameCoreStates::FALLING)
  {
     GameSound::getInstance()->loadChunk(statesSounds.at(1));
  }*/
}

void GameSound::closeAll()
{
  result = system->close();
  ERRCHECK(result);
  
  result = system->release();
  ERRCHECK(result);
}

void GameSound::ERRCHECK(FMOD_RESULT result)
{
  if (result != FMOD_OK)
  {
    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    exit(-1);
  }
}