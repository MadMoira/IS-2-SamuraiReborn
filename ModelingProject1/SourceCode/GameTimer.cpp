
#include "GameTimer.h"

GameTimer::GameTimer(void)
{
	startTicks = pausedTicks = 0;
	paused = started = false;
}


GameTimer::~GameTimer(void)
{
}

void GameTimer::start()
{
	paused = false;
	started = true;
	startTicks = SDL_GetTicks();
}

void GameTimer::stop()
{
	paused = false;
	started = false;
}

void GameTimer::pause()
{
	if(started == true && paused == true){
		paused = true;
		pausedTicks = SDL_GetTicks();
	}
	
}

void GameTimer::unpause()
{
    
    if( paused == true )
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int GameTimer::getTicks()
{
	if( started == true )
    {
        if( paused == true )
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }    
    }

	return 0;
}

