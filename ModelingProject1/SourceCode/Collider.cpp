#include "Collider.h"

#include <algorithm>

Collider::Collider()
{
}

bool Collider::instanceFlag = false;
Collider* Collider::collider = NULL;

Collider* Collider::getInstance()
{
  if( !instanceFlag )
  {
    collider = new Collider();
    instanceFlag = true;
  }
  return collider;
}

void Collider::initializeColliderSprites(boost::ptr_vector< Enemy >* enemiesList, 
	                                     boost::ptr_vector< Player >* playersList)
{
  enemies = enemiesList;
  players = playersList;
}

void Collider::initializeColliderTiles(std::vector< std::vector < Tile > > tilemap,
	                                   std::vector< int > tilesList)
{
  layerMap = tilemap;
  collisionTilesList = tilesList;
}

void Collider::cleanUpResources()
{
  layerMap.clear();
  collisionTilesList.clear();
}

bool Collider::checkCollision(CollisionBox& A, CollisionBox& B, float directionX)
{
  if( ( ( ((A.getY() + A.getHeight()) > B.getY()) && 
		( (A.getX() + A.getWidth()) > (B.getX()) ) && 
		( A.getX() < (B.getX() + B.getWidth()))) || 
		(( (A.getX() + A.getWidth()) > (B.getX()) ) && 
		( A.getX() < (B.getX() + B.getWidth())) && directionX > 0.0f) || 
		(( (A.getX() + A.getWidth()) > (B.getX()) ) && 
		( A.getX() < (B.getX() + B.getWidth())) && directionX < 0.0f)))
  {
    return true;
  }

  return false;
}

bool Collider::checkTileCollision(CollisionBox& A, float directionX)
{
	int dir = 1;
	if ( directionX == 1)
	{
	  dir = -1;
	}
  for(int i = (int)A.getX(); i <= (int)A.getX() + (dir)*(int)A.getWidth(); i += 32)
  {
    for(int j = (int)A.getY(); j <= (int)A.getY() + (dir)*(int)A.getHeight(); j += 32)
	{
      int x = (int)i/32;
      int y = (int)j/32;

      Tile foundTile = layerMap[y][x];
	  if ( foundTile.getID() == 0 )
	  {
		continue;
	  }

	  if( foundTile.getHasCollision() )
	  {
        return true;
      }
    }
  }

  return false;
}

bool Collider::checkEnemiesCollision(CollisionBox& A, float directionX)
{
 /* for(int i = 0; i == enemies->size(); i++)
  {
    if( checkCollision(A, *enemies->at(i).getSprite()->getCollisionBox(), directionX) )
	{
      return true;
    }
  }
  */
  return false;
}
/*
boost::ptr_vector< Enemy > Collider::checkAttackCollision(CollisionBox& A, float directionX)
{
  boost::ptr_vector< Enemy > enemiesCollided;

  for(int i = 0; i == enemies->size(); i++)
  {
    if( checkCollision( A, *enemies->at(i).getSprite()->getCollisionBox(), directionX) )
	{
      enemiesCollided.push_back(&enemies->at(i));
    }
  }
  
  return enemiesCollided;
}*/

/*boost::ptr_vector< Player > checkEnemiesAttackCollision(CollisionBox& A, float directionX)
{
  boost::ptr_vector< Player > playersCollided;
  for(int i = 0; i == players->size(); i++)
  {
    if( checkCollision(A, *players->at(i).getPlayerSprite()->getCollisionBox(), directionX) )
	{
      playersCollided.push_back(&players->at(i));
    }
  }
  return playersCollided;
}*/

bool Collider::onTheGround(CollisionBox& A, float directionX)
{
  	int dir = 1;
	int initialX  = 0;
	if ( directionX == 1)
	{
	  dir = -1;
	}
	if ( dir == -1 )
	{
	  initialX = (int)A.getX() - (int)A.getWidth();
	}
	else
	{
	  initialX = (int)A.getX();
	}

	if ( initialX > 32 )
	{
	  int d = 4;
	}

	int posY = (int)A.getY() + (int)A.getHeight() ;
	int y = ( posY  )/32;

	if ( val + 1 != y && val != 0)
	{

		int d = 4;
	}
	val = y;
	if ( initialX < 0 )
	{
	  initialX = 0;
	}
  for(int i = initialX;i <= initialX + (int)A.getWidth(); i += 32)
  {

    int x = (int)i/32;
		  if ( dir == -1 )
	  {
		  int d = 4;
	  }
		  if ( y > 720.0f/32 )
		  {
			return false;
		  }
    Tile groundTile = layerMap[y][x];
		  if ( x == 125 && y == 21)
	  {
		int d = 4;
	  }
	if( groundTile.getHasCollision() == false)
	{
      return false;
	}
  }	
  return true;
}