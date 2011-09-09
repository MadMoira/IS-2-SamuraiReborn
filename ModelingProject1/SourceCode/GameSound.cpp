#include "GameSound.h"

GameSound::GameSound(void){
	music = NULL;
}

GameSound::~GameSound(){

}

bool GameSound::initSound(){
	if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) != -1){
		return true;
	}
	return false;
}

void GameSound::loadSound(std::string name){

	const char* MusicName = name.c_str();
	music = Mix_LoadMUS(MusicName);
	Mix_PlayMusic(music, -1);

}

void GameSound::loadChunk(std::string name){

	const char* ChunkName = name.c_str();
	effect = Mix_LoadWAV(ChunkName);
	Mix_PlayChannel( -1, effect, 0 );


}