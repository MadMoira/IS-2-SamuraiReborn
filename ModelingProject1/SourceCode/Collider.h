#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "CollisionBox.h"
#include "Enemy.h"
#include "Player.h"
#include "Tile.h"

class Collider
{
  public:
   static Collider* getInstance();
   
   void initializeColliderSprites(boost::ptr_vector< Enemy >* enemies, boost::ptr_vector< Player >* players);
   void initializeColliderTiles(std::vector< std::vector < Tile > > tilemap,
	                            std::vector< int > tilesList);

   void cleanUpResources();
   
   bool checkCollision(CollisionBox& A, CollisionBox& B , float direction);
   bool checkTileCollision(CollisionBox& A, float directionX);
   bool checkEnemiesCollision( CollisionBox& A, float directionX);

   //boost::ptr_vector< Player > checkEnemiesAttackCollision(CollisionBox& A, float directionX);
   //boost::ptr_vector< Enemy > checkAttackCollision(CollisionBox& A, float directionX);

   bool onTheGround(Sprite& A, float directionX);

   void setLayerMap(std::vector< std::vector < Tile > > tilemap) { layerMap = tilemap; }

   void setCollisionTilesList(std::vector< int > tilesList) { collisionTilesList = tilesList; }

  protected:
   Collider();

  private:
   static bool instanceFlag;
   static Collider* collider;
   std::vector< std::vector < Tile > > layerMap;
   std::vector< int > collisionTilesList;
   boost::ptr_vector< Enemy >* enemies;
   boost::ptr_vector< Player >* players;
};