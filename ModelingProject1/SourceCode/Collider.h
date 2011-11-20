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
   
   void initializeColliderSprites(boost::ptr_vector< Enemy >* enemiesList, boost::ptr_vector< Player >* playersList);
   void addLayerTilemap(std::vector< std::vector < Tile > > layer); 

   void cleanUpResources();
   
   bool checkCollision(CollisionSystem::CollisionBox& A, CollisionSystem::CollisionBox& B , float direction);
   void checkTileCollision(CollisionSystem::CollisionBox& A, int directionX,  int directionY, 
	                       CollisionSystem::DirectionsMove& directionsMove);

   bool checkStateCollisionPlayer( Sprite& playerSprite );
   bool checkStateCollisionXAxis( Sprite& playerSprite );
   GLfloat recalculateSpriteBoxPosition( float initialPosition, float offsetPosition, int direction );

   void checkBoxBordersCollision( CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove,
	                              int leftPositionBorder, int currentPosition, int positionY );
   void checkTopBoxCollision( CollisionSystem::DirectionsMove& directionsMove, int topY, int directionY, int currentPositionY );
   void checkBodyBoxCollision( CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, int directionX, 
	                           int directionY, int currentPositionY );
   void checkBottomBoxCollision( CollisionSystem::DirectionsMove& directionsMove, int bottomY, int directionX, 
	                             int directionY, int currentPositionY );
   bool checkEnemiesCollision( CollisionSystem::CollisionBox& A, float directionX );

   //std::vector< Player > checkEnemiesAttackCollision(CollisionSystem::CollisionBox& A, float directionX);
   //boost::ptr_vector< Enemy > checkAttackCollision(CollisionSystem::CollisionBox& A, float directionX);

   bool onTheGround(CollisionSystem::CollisionBox& A, int directionX, int directionY);

  protected:
   Collider();

  private:
   static bool instanceFlag;
   static Collider* collider;
   std::vector< std::vector< std::vector < Tile > > > layers;
   boost::ptr_vector< Enemy >* enemies;
   boost::ptr_vector< Player >* players;
};