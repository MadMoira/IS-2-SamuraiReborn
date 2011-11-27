#pragma once

#include "GameConfiguration.h"
#include "GameSaves.h"
#include "GameScreen.h"
#include "GameTimer.h"
#include "GameSound.h"

#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"

#include "Vector.h"

class GameCore
{
  public:
   GameCore(void);
   ~GameCore(void);

   bool initializeGameCore();
   bool cleanUpGameCore();

   void initializePlayers();

   GameTimer* getGameTimer() { return timer; }
   void startTimer();

   GameSound* getGameSound() { return sound; };
   void startMusic(std::string filename);
   void startSoundEffect(std::string filename);

   Camera* getCamera() { return camera; };
   void resetCamera(GLfloat level, GLfloat spawningPoint);

   GameScreen* getGameScreen() { return screen; };

   boost::ptr_vector< Player >& getPlayersList() { return playersList; }
   boost::ptr_vector< Enemy >& getEnemyList() { return enemiesList; }

   void addPlayerToGame(Player *player, IDSprites id, std::string filename, std::vector< Vector2f> speed,
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
				std::vector< Vector2f> delayMovement);
   void addEnemyToGame(Enemy *enemy, IDSprites id, std::string filename, std::vector< Vector2f> speed,
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
				GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
				std::vector< Vector2f> delayMovement);

   bool getIsRunning() { return isRunning; }
   void setIsRunning(bool running) { isRunning = running; };
	
  private:
   GameConfiguration* configuration;
   GameSaves* saves;
   GameScreen* screen;
   GameTimer* timer;
   GameSound* sound;
   Camera* camera;
   Collider* collider;

   boost::ptr_vector< Player > playersList;
   boost::ptr_vector< Enemy > enemiesList;
   bool isRunning;
};

