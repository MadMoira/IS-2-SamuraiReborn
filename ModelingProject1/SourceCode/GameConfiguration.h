#pragma once

class GameConfiguration
{
public:
	GameConfiguration(void);
	~GameConfiguration(void);
	void getConfiguration(void);

private:

	int widht;
	int height;
	int difficultyLevel;
	int soundMode;
};

