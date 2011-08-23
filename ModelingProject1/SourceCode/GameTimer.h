#pragma once

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

private:
	int startTicks, pausedTicks;
    bool paused, started;
};

