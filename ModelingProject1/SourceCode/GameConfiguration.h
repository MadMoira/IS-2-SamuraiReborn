#pragma once

class GameConfiguration
{
public:
	GameConfiguration(void);
	~GameConfiguration(void);

private:
	int difficultyLevel;
	int soundMode;
	int screenWidth;
	int screenHeight;
};

