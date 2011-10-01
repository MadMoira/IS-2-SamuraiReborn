#pragma once

#include <boost/ptr_container/ptr_vector.hpp>
#include "GameConfiguration.h"
#include "GameSaves.h"
#include "GameScreen.h"
#include "GameTimer.h"
#include "GameSound.h"
#include "Player.h"

#include "Vector.h"

class GameCore
{
public:
	GameCore(void);
	~GameCore(void);

	void close();

	bool initializeGameCore();
	bool cleanUpGameCore();

	void initializePlayers();

	GameTimer* getGameTimer() { return timer; }
	void startTimer();

	GameSound* getGameSound() { return sound; };
	void startMusic(std::string filename);
	void startSoundEffect(std::string filename);

	boost::ptr_vector< Player > &getPlayersList() { return playersList; }
	void addPlayerToGame(Player *player, IDSprites id, std::string filename, std::vector< Vector2f> speed, GLfloat speedY,
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				IDSpriteStates state, GLfloat widthSprite, GLfloat heightSprite);

	bool getIsRunning() { return isRunning; }
	void setIsRunning(bool running) { isRunning = running; }
	
private:
	GameConfiguration *configuration;
	GameSaves *saves;
	GameScreen *screen;
	GameTimer *timer;
	GameSound *sound;
	boost::ptr_vector< Player > playersList;
	bool isRunning;
};

