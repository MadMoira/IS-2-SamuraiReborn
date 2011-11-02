
#include <algorithm>
#include "PlayerSpriteStates.h"

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

void Collider::addLayerTilemap(std::vector< std::vector < Tile > > layer)
{
  layers.push_back(layer);
}

void Collider::cleanUpResources()
{
  for (std::string::size_type i = 0; i < layers.size(); i++)
  {
	layers.at(i).clear();
  }
}

bool Collider::checkCollision(CollisionSystem::CollisionBox& A, CollisionSystem::CollisionBox& B, float directionX)
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

void Collider::checkTileCollision(CollisionSystem::CollisionBox& A, int directionX,  int directionY,
	                              CollisionSystem::DirectionsMove& directionsMove)
{
  int initialX  = 0;
  int initial = 0;
  
  if ( directionX == SpriteData::LEFT )
  {
    initialX = (int)A.getX() - (int)A.getWidth()/2;
  }
  else
  {
    initialX = (int)A.getX();
  }

  initial = initialX;

  directionsMove.setCanMoveRight(true);
  directionsMove.setCanMoveLeft(true);
  directionsMove.setCanMoveUp(true);
  directionsMove.setCanMoveDown(true);


  for (std::string::size_type indexLayer = 0; indexLayer < layers.size(); indexLayer++)
  {
    for(int i = initialX;i <= initialX + (int)A.getWidth(); i += 32)
    {
      for(int j = (int)A.getY(); j <= (int)A.getY() + (int)A.getHeight(); j += 32)
	  {
        int x = (int)i/32;
        int y = (int)j/32;

        if ( y > 720.0f/32 )
        {
          return;
        }

        Tile foundTile = layers.at(indexLayer)[y][x];

	    if ( foundTile.getID() == 0 )
	    {
		  continue;
	    }
 
	    if ( foundTile.getHasCollision() )
	    {
          checkBoxBordersCollision(A, directionsMove, initial, initialX, y);
		  checkTopBoxCollision(directionsMove, (int)A.getY()/32, directionY, y);
		  checkBodyBoxCollision(A, directionsMove, directionX, directionY, y);
		  return;
        }
      }
    }
  }
}

bool Collider::checkStateCollisionPlayer(Sprite& playerSprite)
{
  if ( !playerSprite.getDirectionsMove().canMoveYUp && !playerSprite.getIsOnGround() && 
        playerSprite.getCurrentState() != GameCoreStates::FALLING )
  {
    playerSprite.changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                         std::list<InputMapping::Key>() );
    playerSprite.setSpeedX(0.0f);
	return true;
  }

  if ( playerSprite.getIsOnGround() && playerSprite.getCurrentState() == GameCoreStates::FALLING )
  {
    GLfloat offsetPosition = recalculateSpriteBoxPosition( playerSprite.getCollisionBox()->getY(), 
		                                                   playerSprite.getCollisionBox()->getHeight() );
	playerSprite.setPositionY(offsetPosition);
    playerSprite.getCollisionBox()->setY( playerSprite.getCollisionBox()->getY() - playerSprite.getCollisionBox()->getOffset().y - 
		                                  offsetPosition );

    playerSprite.changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                         std::list<InputMapping::Key>() );

	playerSprite.setPlayerMoveInX(false);
	playerSprite.setPlayerMoveInY(false);
    return true;
  }

  if ( !playerSprite.getIsOnGround() && !playerSprite.isPlayerOnTheAir() )
  {
    playerSprite.changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                         std::list<InputMapping::Key>() );
    return true;
  }

  return false;
}

bool Collider::checkStateCollisionXAxis(Sprite& playerSprite)
{
  checkStateCollisionPlayer(playerSprite);

  if ( !playerSprite.getPlayerMoveBasedInDirection() && !playerSprite.getIsOnGround() && 
	    playerSprite.getCurrentState() == GameCoreStates::FALLING )
  {
    int animationDirection = playerSprite.getHandlerAnimation()->getAnimationDirection();
    GLfloat offsetPosition = recalculateSpriteBoxPosition(playerSprite.getCollisionBox()->getX(),
		                                                  playerSprite.getCollisionBox()->getOffsetXPosition(animationDirection) );
	playerSprite.setPositionX(offsetPosition);
	playerSprite.getCollisionBox()->setX( playerSprite.getCollisionBox()->getX() - 
		                                  playerSprite.getCollisionBox()->getOffsetXBasedOnDirection(animationDirection) - 
		                                  offsetPosition, animationDirection );
							
	playerSprite.changePreviousPlayerState(GameCoreStates::STILL);
    playerSprite.changeStatePlayerSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                         std::list<InputMapping::Key>() );
	return true;
  }

  if ( !playerSprite.getPlayerMoveBasedInDirection() && playerSprite.getIsOnGround() && 
	     playerSprite.getCurrentState() != GameCoreStates::STILL)
  {
    int animationDirection = playerSprite.getHandlerAnimation()->getAnimationDirection();
    GLfloat offsetPosition = recalculateSpriteBoxPosition(playerSprite.getCollisionBox()->getX(),
		                                                  playerSprite.getCollisionBox()->getOffsetXPosition(animationDirection) );

	playerSprite.setPositionX( (playerSprite.getHandlerAnimation()->returnAnimationDirectionAxisValue()*-1) * offsetPosition);
    playerSprite.getCollisionBox()->setX( playerSprite.getCollisionBox()->getX() - 
		                                  playerSprite.getCollisionBox()->getOffsetXBasedOnDirection(animationDirection) - 
                                          offsetPosition, animationDirection );
    						
    playerSprite.changeStatePlayerSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                         std::list<InputMapping::Key>() );
	playerSprite.setPlayerMoveInX(false);
	playerSprite.setPlayerMoveInY(false);
    return true;
  }

  return false;
}

GLfloat Collider::recalculateSpriteBoxPosition(float initialPosition, float offsetPosition)
{
  GLfloat startingPosition = (initialPosition + offsetPosition)/32;
  int integerPart = (int)startingPosition;
  GLfloat positionOffsetBox = ( (startingPosition - integerPart)*32 );
  
  return positionOffsetBox;
}

void Collider::checkBoxBordersCollision(CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove,
	                                    int leftPositionBorder, int currentPosition, int positionY)
{
  if ( leftPositionBorder == currentPosition && 
	   positionY != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
  {
    directionsMove.setCanMoveLeft(false);
    directionsMove.setCanMoveRight(true);
  }

  if ( leftPositionBorder + (int)A.getWidth()/32 == currentPosition && 
	   positionY != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
  {
    directionsMove.setCanMoveLeft(true);
    directionsMove.setCanMoveRight(false);
  }
}

void Collider::checkTopBoxCollision(CollisionSystem::DirectionsMove& directionsMove, int topY, int directionY,
	                                int currentPositionY)
{
  if ( currentPositionY == topY )
  {
    if ( directionY == SpriteData::UP )
    {
      directionsMove.setCanMoveUp(false);
      directionsMove.setCanMoveDown(true);
    }
    else
    {
      directionsMove.setCanMoveUp(false);
      directionsMove.setCanMoveDown(true);
    }
  }
}

void Collider::checkBodyBoxCollision(CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, 
	                                 int directionX, int directionY, int currentPositionY)
{
  if ( directionX == SpriteData::RIGHT && 
	   currentPositionY != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
  {
    directionsMove.setCanMoveRight(false);
    directionsMove.setCanMoveLeft(true);
  }

  else if ( directionX == SpriteData::LEFT && 
	        currentPositionY != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
  {
    directionsMove.setCanMoveRight(true);
    directionsMove.setCanMoveLeft(false);
  }
}

bool Collider::checkEnemiesCollision(CollisionSystem::CollisionBox& A, float directionX)
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

bool Collider::onTheGround(CollisionSystem::CollisionBox& A, int directionX, int directionY)
{
  int directionPlayer = SpriteData::RIGHT;
  int initialX  = 0;

  initialX = (int)A.getX();

  int positionY = ( (int)A.getY() + (int)A.getHeight() )/32;

  if ( initialX < 0 )
  {
    initialX = 0;
  }

  bool isOnGround = false;

  for (std::string::size_type indexLayer = 0; indexLayer < layers.size(); indexLayer++)
  {
    if ( isOnGround )
    {
      break;
    }

    isOnGround = true;

    for(int i = initialX; i <= initialX + (int)A.getWidth(); i += 32)
    {
      int x = (int)i/32;
      if ( positionY > 720.0f/32 )
      {
        return false;
      }

      Tile groundTile = layers.at(indexLayer)[positionY][x];

	  if( !groundTile.getHasCollision())
	  {
        isOnGround = isOnGround && false;
	  }
    }
  }

  return isOnGround;
}