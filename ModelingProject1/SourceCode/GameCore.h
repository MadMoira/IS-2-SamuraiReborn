#pragma once

#include "GameConfiguration.h"
#include "GameSaves.h"
#include "GameScreen.h"
#include "GameTimer.h"
#include "GameSound.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "GameFont.h"

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

	Camera* getCamera() {return camera;};
	GameScreen* getGameScreen() {return screen;};

	boost::ptr_vector< Player >& getPlayersList() { return playersList; }
	boost::ptr_vector< Enemy >& getEnemyList() { return enemyList; }
	void addPlayerToGame(Player *player, IDSprites id, std::string filename, std::vector< Vector2f> speed,
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				GLfloat widthSprite, GLfloat heightSprite);
	void addEnemyToGame(Enemy *enemy, IDSprites id, std::string filename, std::vector< Vector2f> speed,
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				GLfloat widthSprite, GLfloat heightSprite);

	bool getIsRunning() { return isRunning; }
	void setIsRunning(bool running) { isRunning = running; };
	
private:
	GameConfiguration* configuration;
	GameSaves* saves;
	GameScreen* screen;
	GameTimer* timer;
	GameSound* sound;
	Camera* camera;
	boost::ptr_vector< Player > playersList;
	boost::ptr_vector< Enemy > enemyList;
	bool isRunning;
};

