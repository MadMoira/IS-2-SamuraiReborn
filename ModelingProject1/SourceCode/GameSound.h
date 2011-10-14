#pragma once

#include <string>
#include <fmod.hpp>
#include <fmod_errors.h>

class GameSound 
{
  public:
   GameSound(void);
   ~GameSound();

   bool initSound();
   void loadSound(std::string name);
   void loadChunk(std::string name);
		
   void upVolumeSE();
   void downVolumeSE();
   void upVolumeMUS();
   void downVolumeMUS();
	
   void closeAll();

   void ERRCHECK(FMOD_RESULT);
		
  private:
   FMOD::System* system;
   FMOD::Sound* sound;
   FMOD::Sound* chunks[3];
   FMOD::Channel* channel[2];
   FMOD_RESULT result;
};