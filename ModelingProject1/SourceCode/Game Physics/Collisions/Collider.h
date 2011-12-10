#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "CollisionBox.h"
#include "Enemy.h"
#include "Player.h"
#include "Tilemap.h"

class Collider
{
  public:
   static Collider* getInstance();
   
   void initializeColliderSprites(boost::ptr_vector< Characters::Enemy >* enemiesList, 
                                  boost::ptr_vector< Characters::Player >* playersList);
   void addLayerTilemap(std::vector< std::vector < Tile > > layer);
   
   void setLevelLength(int length) { levelLength = length; }

   void cleanUpResources();
   
   bool checkCollision(CollisionSystem::CollisionBox& A, CollisionSystem::CollisionBox& B , float direction);
   void checkTileCollisionY(CollisionSystem::CollisionBox& A, GLfloat* speedX, GLfloat* speedY, int directionX,  int directionY, 
                           CollisionSystem::DirectionsMove& directionsMove, int currentMovement);
   void checkTileCollisionX(CollisionSystem::CollisionBox& A, GLfloat* speedX, GLfloat* speedY, int directionX,  int directionY, 
                           CollisionSystem::DirectionsMove& directionsMove, int currentMovement);

   void checkBoxBordersCollision( CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove,
                                  int leftPositionBorder, int rightPositionBorder, int currentPosition, int positionY );
   void checkTopBoxCollision( CollisionSystem::DirectionsMove& directionsMove, int topY, int directionY, int currentPositionY );
   void checkBodyBoxCollision( CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, int directionX, 
                               int directionY, int currentPositionY );
   void checkBottomBoxCollision( CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, 
                                 int directionX, int directionY, int currentPositionX, int currentPositionY,
                                 int currentMovement);

   bool checkStateCollisionPlayer( Sprite& playerSprite );
   bool checkStateCollisionXAxis( Sprite& playerSprite );
   bool checkStatePhysicsModes( Sprite& playerSprite );
   GLfloat recalculateSpriteBoxPosition( float initialPosition, float offsetPosition, int direction );

   bool checkEnemiesCollision( CollisionSystem::CollisionBox& A, float directionX );

   //boost::ptr_vector< Characters::Player > checkEnemiesAttackCollision(CollisionBox& A, float directionX);
   //boost::ptr_vector< Characters::Enemy > checkAttackCollision(CollisionBox& A, float directionX);

   bool onTheGround(CollisionSystem::CollisionBox& A, int directionX, int directionY);

   bool checkPositionWithinLevelLength(CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, 
	                                   Vector2f speed, int directionX);

  protected:
   Collider();

  private:
   static bool instanceFlag;
   static Collider* collider;
   int levelLength;
   std::vector< std::vector< std::vector < Tile > > > layers;
   boost::ptr_vector< Characters::Enemy >* enemies;
   boost::ptr_vector< Characters::Player >* players;
};