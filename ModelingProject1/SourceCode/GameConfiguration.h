#pragma once

class GameConfiguration
{
public:
	GameConfiguration(void);
	~GameConfiguration(void);
	void getConfiguration(void);

private:
	int width;
	int height;
	int difficultyLevel;
	int soundMode;
	int screenWidth;
	int screenHeight;
};

