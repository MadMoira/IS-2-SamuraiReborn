#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "GameConfiguration.h"
#include "GameSaves.h"
#include "GameScreen.h"
#include "GameTimer.h"
#include "GameSound.h"
#include "Player.h"

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
	void addPlayerToGame(Player *player);

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

