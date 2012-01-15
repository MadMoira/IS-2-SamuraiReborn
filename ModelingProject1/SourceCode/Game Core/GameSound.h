#pragma once

#include <string>
#include <vector>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <PlayerSpriteStates.h>
#include <File.h>

/* **ID's**
SoundID: 
	0 = characterSound
	1 = Menu/LevelSound
StateID: 
	0 = attackSound
	1 = groundhitSound
	2 = runningSound
**Files Layout**
Musics.txt:
	0 = Panda sounds
	1 = Meerkat Sounds
LevelSounds.txt:
	0 = Level One
	1 = SMainMenu
		0 = Background Music 
		1 = Selection sound
	2 = SPlayerSelection
		0 = Background Music 
		1 = Selection sound

**Channels**
Channel[0] = SE = on going sounds
Channel[1] = MUS = one time, multiple use sounds, chunks
Channel[2] = RS = partial duration sounds
*/

class GameSound 
{
  public:
   GameSound(void);
   ~GameSound();

   static GameSound* getInstance();
   bool initSound();
   void closeAll();
   void ERRCHECK(FMOD_RESULT);

   void initSounds(int characterID, int soundType);
   void splitFileSounds(std::string line, int soundType);

   void upVolume(int channelID, float increasingValue);
   void downVolume(int channelID, float decreasingValue);
   float getVolume(int channelID);
   
   void upOverallVolume(float increasingValue);
   void downOverallVolume(float decreasingValue);

   void loadChunk(int row, int soundType, int soundID);
   void loadSound(int row, int soundType, int soundID);
   void playSound(int row, int soundType, int soundID);
   void closeSound();

   void stateSoundsHandling(GameCoreStates::SpriteState previousState);
        
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
   FMOD::Channel* channel[3];
   FMOD_RESULT result;
};