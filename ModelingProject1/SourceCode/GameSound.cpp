#include "GameSound.h"

GameSound::GameSound(void)
{
	result = FMOD::System_Create(&system);
	printf("FMOD created");
	ERRCHECK(result);
	//The file structure will be: attackSound;groundhitSound;runningSound;others....
	sFilename = "Musics.txt";
	lFilename = "LevelSounds.txt";
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
	std::string name = statesSounds.at(i);
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

void GameSound::stateSoundsHandling(GameCoreStates::SpriteState previousState){
	 if(previousState == GameCoreStates::RUNNING){
	  GameSound::getInstance()->closeSound();
  }
  if(previousState == GameCoreStates::FALLING){
	  GameSound::getInstance()->loadChunk(statesSounds.at(1));
  }
}

void GameSound::loadChunk(std::string name)
{
	if(name == "none"){
		return;
	}
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

//additions
std::string GameSound::readLineFromFile(string sFilename, int row){
	std::string line;
	ifstream soundsFile ( sFilename, ifstream::in );
	if(!soundsFile.is_open()){
		exit(1);
	}
	char n;
	int i=0;
	while (soundsFile.good()){
        n=soundsFile.get();
		if(i==row){
			line+=n;
		}
		if(n=='\n'){
			i++;
		}
	}
	line.erase(line.size()-1);
	soundsFile.close();
	return line;
}

void GameSound::split(std::string line, int soundType){
	std::string temp;

	for(int i=0;i<line.size();i++){
		if(line.at(i)==';' && temp!=""){
			if(soundType==0){
	statesSounds.push_back(temp);
	}else{
		ambienceSounds.push_back(temp);
	}	
			temp="";
		}else{
			temp+=line.at(i);
	    }
	}
}

void GameSound::initSounds(int row, int soundType){
	std::string line;
	if(soundType==0){
	line= readLineFromFile(sFilename ,row);
	}else{
		line= readLineFromFile(lFilename ,row);
	}
	split(line, soundType);
}

void GameSound::loadChunk(int row, int soundType, int soundID){

	initSounds(row, soundType);
	std::string name;
		if(soundType==0){
	name = statesSounds.at(soundID);
	}else{
	name = ambienceSounds.at(soundID);
	}
		
	if(name == "none"){
		return;
	}

	const char* ChunkName = name.c_str();
	result = system->createSound(ChunkName, FMOD_LOOP_OFF, 0, &chunks[0]);
	ERRCHECK(result);
	result = system->playSound(FMOD_CHANNEL_FREE, chunks[0], false, &channel[1]);
	ERRCHECK(result);
	result = channel[1]->setVolume(0.1f);
}


void GameSound::loadSound(int row, int soundType, int soundID){
	initSounds(row, soundType);
	std::string name;
		if(soundType==0){
	name = statesSounds.at(soundID);
	}else{
	name = ambienceSounds.at(soundID);
	}

	if(name == "none"){
		return;
	}
	const char* MusicName = name.c_str();
	printf("Loading");
	result = system->createStream(MusicName, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
	ERRCHECK(result);
	printf("Playing");
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel[0]);
	ERRCHECK(result);
}

void GameSound::PlaySound(int row, int soundType, int soundID){
	initSounds(row, soundType);
	std::string name;
		if(soundType==0){
	name = statesSounds.at(soundID);
	}else{
	name = ambienceSounds.at(soundID);
	}
	if(name == "none"){
		return;
	}
	currentSound = name.c_str();
	result = system->createStream( currentSound, FMOD_DEFAULT, 0, &sound );
	ERRCHECK(result);
	result = system->playSound( FMOD_CHANNEL_REUSE, sound, false, &channel[2]);
	ERRCHECK(result);
}
//