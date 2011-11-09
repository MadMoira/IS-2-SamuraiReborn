#pragma once

#include <SDL/SDL.h>

#define FRAMES_PER_SECOND 10

class GameTimer
{
  public:
   GameTimer(void);
   ~GameTimer(void);

   void start();
   void stop();
   void delay();
   void pause();
   void unpause();

   int getTicks();

   bool isStarted();
   bool isPaused();

   void setFramesPerSecond(int fps) { framesPerSecond = fps; }

  private:
   int startTicks, pausedTicks;
   bool paused, started;
   int framesPerSecond;
};

