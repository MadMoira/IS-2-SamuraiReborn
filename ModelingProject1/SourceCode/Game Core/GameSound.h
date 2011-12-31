#pragma once

#include <string>
#include <vector>
#include <fmod.hpp>
#include <fmod_errors.h>

#include <PlayerSpriteStates.h>

#include <File.h>

class GameSound 
{
  public:
   GameSound(void);
   ~GameSound();

   static GameSound* getInstance();
   bool initSound();
   void closeSound();

   void initSounds(int characterID, int soundType);
   void splitFileSounds(std::string line, int soundType);
        
   void upVolumeSE();
   void downVolumeSE();
   void upVolumeMUS();
   void downVolumeMUS();

   void loadChunk(int row, int soundType, int soundID);
   void loadSound(int row, int soundType, int soundID);
   void playSound(int row, int soundType, int soundID);
   void stateSoundsHandling(GameCoreStates::SpriteState previousState); 
    
   void closeAll();

   void ERRCHECK(FMOD_RESULT);
        
  private:
   std::vector< std::string > ambienceSounds;
   std::vector< std::string > statesSounds;

   std::string sFilename;
   std::string lFilename;

   static bool instanceFlag;
   const char* currentSound;
   static GameSound* gameSound;

   FMOD::System* system;
   FMOD::Sound* sound;
   FMOD::Sound* chunks[3];
   FMOD::Channel* channel[2];
   FMOD_RESULT result;
};