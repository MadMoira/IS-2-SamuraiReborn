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

   boost::ptr_vector< Characters::Player >& getPlayersList() { return playersList; }
   boost::ptr_vector< Characters::Enemy >& getEnemyList() { return enemiesList; }

   void addPlayerToGame(Characters::Player* player, SpriteData::IDSprites id, std::string filename, Vector2f pos, 
	            int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement);
   void addEnemyToGame(Characters::Enemy* enemy, SpriteData::IDSprites id, std::string filename,
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement);

   void initializeSpriteCollisionBoxPlayer(SpriteData::IDSprites id, float width, float height, GLfloat offsetX, GLfloat offsetY);
   void initializeRigidBodyVectors(SpriteData::IDSprites id, std::vector< Vector2f > maxSpeed);
   void setIDNumberOfPlayer(SpriteData::IDSprites id, int idPlayer);

   bool getIsRunning() { return isRunning; }
   void setIsRunning(bool running) { isRunning = running; };

   void pushBackPlayerToInitialize(int id) { playersInitialized.push_back(id); }
   std::vector< int > getPlayersToInitialize() { return playersInitialized; }
   void clearPlayerToInitialize() { playersInitialized.clear(); }
    
  private:
   GameConfiguration* configuration;
   GameSaves* saves;
   GameScreen* screen;
   GameTimer* timer;
   GameSound* sound;
   Camera* camera;
   Collider* collider;

   boost::ptr_vector< Characters::Player > playersList;
   boost::ptr_vector< Characters::Enemy > enemiesList;
   std::vector< int > playersInitialized;
   bool isRunning;
};

