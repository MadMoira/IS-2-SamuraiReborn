#pragma once

#include <string>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include "PlayerSpriteStates.h"

class GameSound 
{
  public:
	  
   GameSound(void);
   ~GameSound();

   static GameSound* getInstance();
   bool initSound();
   void loadSound(std::string name);
   void loadChunk(std::string name);
   void PlaySound(int i);
   void closeSound();
   void upVolumeSE();
   void downVolumeSE();
   void upVolumeMUS();
   void downVolumeMUS();
   void stateSoundsHandling(GameCoreStates::SpriteState previousState);	
   void closeAll();

   void ERRCHECK(FMOD_RESULT);

   boost::ptr_vector< std::string > Sounds;
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