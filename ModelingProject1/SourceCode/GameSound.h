#pragma once

#include <string>
#include <fmod.hpp>
#include <fmod_errors.h>

class GameSound 
{
  public:
	  
   GameSound(void);
   ~GameSound();

   static GameSound* getInstance();
   bool initSound();
   void loadSound(std::string name);
   void loadChunk(std::string name);
   void PlaySound(std::string name);
   void closeSound();
   void upVolumeSE();
   void downVolumeSE();
   void upVolumeMUS();
   void downVolumeMUS();
	
   void closeAll();

   void ERRCHECK(FMOD_RESULT);
		
  private:
   static bool instanceFlag;
   const char* currentSound;
   static GameSound* gameSound;
   FMOD::System* system;
   FMOD::Sound* sound;
   FMOD::Sound* chunks[3];
   FMOD::Channel* channel[3];
   FMOD_RESULT result;
};