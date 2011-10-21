#include "Collider.h"


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

void Collider::initializeColliderTiles(std::vector< std::vector < Tile > > tilemap)
{
}

void Collider::cleanUpResources()
{
  layerMap.clear();
}

//Method to check for collisions between two collision boxes
bool Collider::checkCollision( CollisionBox& A, CollisionBox& B, float directionX)
{
	//Collisions for left to right, right to left and up to down
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

bool Collider::checkTileCollision(Sprite& A, float directionX)
{
  for(int i = (int)A.getPosX(); i <= (int)A.getWidth(); i++)
  {
    for(int j = (int)A.getPosY(); j <= (int)A.getHeight(); j++)
	{
      Tile foundTile = layerMap[i][j];
      if( foundTile.getID() != 0 )
	  {
        return true;
      }
    }
  }

  return false;
}

bool Collider::checkEnemiesCollision(CollisionBox& A, float directionX)
{
  for(int i = 0; i == enemies->size(); i++)
  {
    if( checkCollision(A, *enemies->at(i).getSprite()->getCollisionBox(), directionX) )
	{
      return true;
    }
  }

  return false;
}

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
}

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

bool Collider::onTheGround(Sprite&A, float directionX)
{
  for(int i = (int)A.getPosX();i <= (int)A.getWidth(); i++)
  {
    Tile groundTile = layerMap[i][(int)A.getPosY()];
    if( groundTile.getID() == 0 )
	{
      return true;
	}
  }	
  return false;
}