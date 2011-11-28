#pragma once

#include <string>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "PlayerSpriteStates.h"
using namespace std;

class GameSound 
{
  public:
   GameSound(void);
   ~GameSound();

   static GameSound* getInstance();
   bool initSound();
   void loadSound(std::string name); //deprecated
   void loadChunk(std::string name); //deprecated
   void PlaySound(int SoundID); //deprecated
   void closeSound();
   void upVolumeSE();
   void downVolumeSE();
   void upVolumeMUS();
   void downVolumeMUS();
   void initSounds(int CharacterID);
   std::string readLineFromFile(string filename, int row);
   void split(std::string line);
   void loadChunk(int CharacterID, int soundID);
   void loadSound(int CharacterID, int soundID);
   void PlaySound(int CharacterID, int soundID);
   void stateSoundsHandling(GameCoreStates::SpriteState previousState);	
   void closeAll();

   void ERRCHECK(FMOD_RESULT);
  
  private:
   std::vector< std::string > ambienceSounds;//Yet to implement if needed
   std::vector< std::string > statesSounds;
   std::string filename;
   static bool instanceFlag;
   const char* currentSound;
   static GameSound* gameSound;
   FMOD::System* system;
   FMOD::Sound* sound;
   FMOD::Sound* chunks[3];
   FMOD::Channel* channel[3];
   FMOD_RESULT result;
};