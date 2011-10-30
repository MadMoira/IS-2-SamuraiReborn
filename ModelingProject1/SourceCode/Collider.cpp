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

bool Collider::checkTileCollision(CollisionBox& A, int directionX,  int directionY,
	                              CollisionSystem::DirectionsMove& directionsMove)
{
  directionsMove.setCanMoveRight(true);
  directionsMove.setCanMoveLeft(true);
  directionsMove.setCanMoveUp(true);
  directionsMove.setCanMoveDown(true);

	int dir = 1;
	int initialX  = 0;
	int initial = 0;
	if ( directionX == 1)
	{
	  dir = -1;
	}

    if ( dir == -1 )
	{
		/*if ( directionY == SpriteData::NO_DIRECTION )
		{*/
			initialX = (int)A.getX() - (int)A.getWidth()/2;
			initial = initialX;
		/*}
		else
		{
			initialX = (int)A.getX();
			initial = initialX;
		}*/
	  
	}
	else
	{
	  initialX = (int)A.getX();
	  initial = initialX;
	}
  for(int i = initialX;i <= initialX + (int)A.getWidth(); i += 32)
  {
    for(int j = (int)A.getY(); j <= (int)A.getY() + (int)A.getHeight(); j += 32)
	{
      int x = (int)i/32;
      int y = (int)j/32;

	  		  if ( y > 720.0f/32 )
		  {
			return false;
		  }
      Tile foundTile = layerMap[y][x];
	  if ( foundTile.getID() == 0 )
	  {
		continue;
	  }




	  if( foundTile.getHasCollision() )
	  {

		  if ( initial == initialX && y != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
		  {
			  directionsMove.setCanMoveLeft(false);
			  directionsMove.setCanMoveRight(true);
		  }

		  if ( initial+32 == initialX && y != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
		  {
			  directionsMove.setCanMoveLeft(true);
			  directionsMove.setCanMoveRight(false);

		  }
		  			  if ( y == (int)A.getY()/32 )
			  {
				  if ( directionY == SpriteData::UP )
				  {
					  directionsMove.setCanMoveUp(false);
					  directionsMove.setCanMoveDown(true);
				  }
				  else
				  {
                      directionsMove.setCanMoveUp(true);
					  directionsMove.setCanMoveDown(false);
				  }
			  }

					/*  if ( y == ( (int)A.getY() + (int)A.getHeight() ) / 32 )
					  {

						  				  if ( directionY == SpriteData::UP )
				  {
					  directionsMove.setCanMoveUp(false);
					  directionsMove.setCanMoveDown(true);
				  }
				  else
				  {

                      directionsMove.setCanMoveUp(true);
					  directionsMove.setCanMoveDown(false);
				  }
					  }*/

		  if ( directionX == SpriteData::RIGHT && y != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
		  {
			  directionsMove.setCanMoveRight(false);
			  directionsMove.setCanMoveLeft(true);
		  }
		  else if ( directionX == SpriteData::LEFT && y != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
		  {
			  						  				  if ( directionY == SpriteData::UP )
				  {
					   directionsMove.setCanMoveRight(true);
			  directionsMove.setCanMoveLeft(false);
				  }
				  else if ( directionY == SpriteData::DOWN )
				  {
                      directionsMove.setCanMoveRight(true);
			  directionsMove.setCanMoveLeft(false);
				  }
				  else
				  {
			  directionsMove.setCanMoveRight(true);
			  directionsMove.setCanMoveLeft(false);
				  }
		  }
        return true;
      }
    }
  }

  directionsMove.setCanMoveRight(true);
  directionsMove.setCanMoveLeft(true);

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

bool Collider::onTheGround(CollisionBox& A, int directionX, int directionY)
{
  	int dir = 1;
	int initialX  = 0;
		if ( directionX == 1)
	{
	  dir = -1;
	}
	if ( dir == -1 )
	{
        if ( directionY == SpriteData::NO_DIRECTION )
		{
			initialX = (int)A.getX() - (int)A.getWidth()/2;
		}
		else
		{
			initialX = (int)A.getX();
		}
	}
	else
	{
	  initialX = (int)A.getX();
	}

	float posY = A.getY() + A.getHeight();
	int pe = (int)posY;
	int y = ( pe  )/32;

	if ( initialX < 0 )
	{
	  initialX = 0;
	}
  for(int i = initialX;i <= initialX + (int)A.getWidth(); i += 32)
  {

    int x = (int)i/32;
	if ( x == 9 && y == 17)
	{
	   int d = 4;
	}
		  if ( y > 720.0f/32 )
		  {
			return false;
		  }
    Tile groundTile = layerMap[y][x];

	if( groundTile.getHasCollision() == false)
	{
      return false;
	}
  }	
  return true;
}