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
   void initSounds(int CharacterID, int soundType);
   std::string readLineFromFile(string filename, int row);
   void split(std::string line, int soundType);
   void loadChunk(int row, int soundType, int soundID);
   void loadSound(int row, int soundType, int soundID);
   void PlaySound(int row, int soundType, int soundID);
   void stateSoundsHandling(GameCoreStates::SpriteState previousState);	
   void closeAll();

   void ERRCHECK(FMOD_RESULT);
  
  private:
   std::vector< std::string > ambienceSounds;//Yet to implement if needed
   std::vector< std::string > statesSounds;
   std::string sFilename;
   std::string lFilename;
   static bool instanceFlag;
   const char* currentSound;
   static GameSound* gameSound;
   FMOD::System* system;
   FMOD::Sound* sound;
   FMOD::Sound* chunks[3];
   FMOD::Channel* channel[3];
   FMOD_RESULT result;
};