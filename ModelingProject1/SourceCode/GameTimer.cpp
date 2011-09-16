
#include "GameTimer.h"

GameTimer::GameTimer(void)
{
	startTicks = pausedTicks = 0;
	paused = started = false;
}


GameTimer::~GameTimer(void)
{
}
