
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
    started = true;
    paused = false;

    startTicks = SDL_GetTicks();
}

void GameTimer::stop()
{
    started = paused = false;
}

void GameTimer::delay()
{
	if( getTicks() < 1000 / FRAMES_PER_SECOND )
    {
		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - getTicks() );
    }
}

void GameTimer::pause()
{
    if( ( started == true ) && ( paused == false ) )
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
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

bool GameTimer::isStarted()
{
    return started;
}

bool GameTimer::isPaused()
{
    return paused;
}

