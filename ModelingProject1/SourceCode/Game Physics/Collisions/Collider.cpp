
#include <algorithm>
#include "PlayerSpriteStates.h"

#include "Collider.h"

#include "PhysicModes.h"

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

void Collider::initializeColliderSprites(boost::ptr_vector< Characters::Enemy >* enemiesList, 
                                         boost::ptr_vector< Characters::Player >* playersList)
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

void Collider::checkTileCollision(CollisionSystem::CollisionBox& A, GLfloat* speedX, GLfloat* speedY, int directionX, int directionY, 
                                  CollisionSystem::DirectionsMove& directionsMove, int currentMovement)
{
  int initialX  = 0;
  int initial = 0;
  int constantDirectionY = -1;

  if ( directionY == SpriteData::UP )
  {
	 constantDirectionY = 1;
  }

  initialX = (int)A.getX();
  initial = initialX;

  directionsMove.setCanMoveRight(true);
  directionsMove.setCanMoveLeft(true);
  directionsMove.setCanMoveUp(true);
  directionsMove.setCanMoveDown(true);

  int constant = 2;
  GLfloat s = 0, sy = 0;

  for (std::string::size_type indexLayer = 0; indexLayer < layers.size(); indexLayer++)
  {
	  s = 0;
	  sy = 0;

	  if ( A.getX()  >= 2251 && indexLayer == 1 )
	  {
		int c = 4;
	  }
	for ( int k = initialX; k<= initialX + *speedX; k += 1)
		{
			if ( s == *speedX )
			{
			int p = 4;
			}
			int constantWidth = (int)A.getWidth();
			int constantXInitial = (int)A.getWidth();
			if ( k == initialX )
			{
			  constantWidth = (int)A.getWidth();
			  constantXInitial = 0;
			}
			for(int i = k + constantXInitial; i <= k + constantWidth; i += 2)
			{
							if ( i >= 2336 && indexLayer == 1)
			{
				int a = 4;
			}
							int axisY = 1;
							if (directionY == SpriteData::UP )
							{
							  axisY = -1;
							}

							int up = 1;
							if ( directionY == SpriteData::UP )
							{
							  up = 0;
							}

				 for ( int m = (int)A.getY() + up*(A.getHeight()); ; m += 1*(axisY))
		        {

					if ( directionY == SpriteData::UP )
					{
					  if ( m <= (int)A.getY() + (*speedY) )
					  {
						break;
					  }
					}

					if ( directionY == SpriteData::NO_DIRECTION )
					{
										  if ( m > (int)A.getY() + (int)A.getHeight() )
					  {
						break;
					  }
					}

						if ( directionY == SpriteData::DOWN   )
					{
					  if ( m <= (int)A.getY() + (int)A.getHeight() + (*speedY) )
					  {
						break;
					  }
					}
					int constantHeight = (int)A.getHeight();
					int constantYInitial = (int)A.getHeight();
					if ( m == (int)A.getY() )
					{
					  constantHeight = (int)A.getHeight();
					  constantYInitial = 0;
					}

					  for(int j = m ; j < m + constantHeight; j += 8)
					  {
						int x = (int)i/32;
						int y = (int)j/32;

						if ( x > 6400.0f/32 || y > 720.0f/32 )
						{
						  return;
						}

						if ( x == 73 && y >= 15 && indexLayer == 1)
						{
							int d = 4;
						}

						Tile foundTile = layers.at(indexLayer)[y][x];

						if ( foundTile.getID() == 0 )
						{
						  continue;
						}
 
						if ( foundTile.getHasCollision() )
						{
							CollisionSystem::CollisionBox* temp = new CollisionSystem::CollisionBox();
							if ( s == 0.0f )
							{
								*temp = A;
							}
							else
							{
							temp = new CollisionSystem::CollisionBox(k, m, A.getWidth(), A.getHeight(), A.getOffset());
							}
						  checkBoxBordersCollision(*temp, directionsMove, k, k + 85, k, y);
						  //checkTopBoxCollision(directionsMove, int topY, int directionY, int currentPositionY);
						  checkBottomBoxCollision(*temp, directionsMove, directionX, directionY, x, y, currentMovement);
						  checkBodyBoxCollision(*temp, directionsMove, directionX, directionY, y);
						  if ( s == 0.0f || sy == 0.0f)
							  return;
						  *speedX = s;
						  if ( *speedY != 0.0f)
						  {
							*speedY = sy;
						  }
						  
		  
						  return;
						} //If Collisions
					} //If For Y
			  sy += 1.0f;
				 } //If For M

	  
			} //If For i
		s += 1.0f;
		} // If For K
  } //If For IndexLayer
}

void Collider::checkBoxBordersCollision(CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove,
                                        int leftPositionBorder, int rightPositionBorder, int currentPosition, int positionY)
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

  if ( rightPositionBorder == currentPosition &&
	   positionY != ( (int)A.getY() + (int)A.getHeight() ) / 32 )
  {
    directionsMove.setCanMoveLeft(true);
    directionsMove.setCanMoveRight(false);
  }
}

void Collider::checkBottomBoxCollision(CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, 
                                       int directionX, int directionY, int currentPositionX, int currentPositionY,
                                       int currentMovement)
{
  int bottomY = ( (int)A.getY() + (int)A.getHeight() ) / 32;

  if ( currentPositionY == bottomY )
  {
    switch(directionX)
    {
      case SpriteData::RIGHT:
      {
        if ( currentPositionX == (int)(A.getX() + A.getWidth())/32 && 
             currentMovement == GamePhysics::X )
        {
          directionsMove.setCanMoveLeft(true);
          directionsMove.setCanMoveRight(false);
        }
        break;
      }
      case SpriteData::LEFT:
      {
        if ( currentPositionX == (int)(A.getX())/32 && 
             currentMovement == GamePhysics::X )
        {
          directionsMove.setCanMoveLeft(false);
          directionsMove.setCanMoveRight(true);
        }
        break;
      }
    }
  }
}

void Collider::checkTopBoxCollision(CollisionSystem::DirectionsMove& directionsMove, int topY, int directionY,
                                    int currentPositionY)
{
  if ( currentPositionY == topY )
  {
    if ( directionY == SpriteData::UP || directionY == SpriteData::DOWN )
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

bool Collider::checkStateCollisionPlayer(Sprite& playerSprite)
{
  if ( !playerSprite.getDirectionsMove().canMoveYUp && !playerSprite.getIsOnGround() && 
        playerSprite.getCurrentState() != GameCoreStates::FALLING )
  {
    playerSprite.changeStateSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                         std::list<InputMapping::Key>() );
    playerSprite.setSpeedX(0.0f);
    playerSprite.setSpeedY(4.0f);
    playerSprite.getHandlerAnimation()->changeDirectionY(4.0f);
    return true;
  }

  if ( playerSprite.getIsOnGround() && playerSprite.getCurrentState() == GameCoreStates::FALLING )
  {
    GLfloat previousPosition = playerSprite.getPosX();
    GLfloat offsetPosition = recalculateSpriteBoxPosition( playerSprite.getCollisionBox()->getY(), 
                                                           playerSprite.getCollisionBox()->getHeight(),
                                                           playerSprite.getHandlerAnimation()->getDirectionY() + 5 );
    playerSprite.setPositionY(offsetPosition);
    playerSprite.getCollisionBox()->setY( playerSprite.getCollisionBox()->getY() - playerSprite.getCollisionBox()->getOffset().y - 
                                          offsetPosition );


    checkStatePhysicsModes(playerSprite);
    
    playerSprite.setPlayerCanMoveYUp(true);
    playerSprite.setPlayerCanMoveYDown(false);
    playerSprite.setPlayerMoveInY(false);
    return true;
  }

  if ( !playerSprite.getIsOnGround() && !playerSprite.isPlayerOnTheAir() )
  {
    playerSprite.changeStateSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
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
                                                          playerSprite.getCollisionBox()->getOffsetXPosition(animationDirection),
                                                          animationDirection);
    /*playerSprite.setPositionX( (playerSprite.getHandlerAnimation()->returnAnimationDirectionAxisValue()) * offsetPosition);
    playerSprite.getCollisionBox()->setX( playerSprite.getPosX() - 
                                         ( (playerSprite.getHandlerAnimation()->returnAnimationDirectionAxisValue() )*
                                          playerSprite.getCollisionBox()->getOffset().x ) + 
                                          playerSprite.getCollisionBox()->getOffsetXBasedOnDirection(animationDirection), 
                                          animationDirection );*/
		playerSprite.setNormalPositionX( playerSprite.getSpeedX() );
    playerSprite.getCollisionBox()->setX(playerSprite.getPosX(), playerSprite.getHandlerAnimation()->getAnimationDirection());
                            
    playerSprite.changePreviousPlayerState(GameCoreStates::STILL);
    playerSprite.changeStateSprite(new GameCoreStates::FallingState(GameCoreStates::FALLING), 0, 
                                         std::list<InputMapping::Key>() );
    return true;
  }

  if ( !playerSprite.getPlayerMoveBasedInDirection() && playerSprite.getIsOnGround() && 
        playerSprite.getCurrentState() != GameCoreStates::STILL )
  {
    int animationDirection = playerSprite.getHandlerAnimation()->getAnimationDirection();
    /*GLfloat offsetPosition = recalculateSpriteBoxPosition(playerSprite.getCollisionBox()->getX(),
                                                          playerSprite.getCollisionBox()->getOffsetXPosition(animationDirection),
                                                          animationDirection);

		if (   offsetPosition > 10 )
	{
	int d = 4;
	}

    playerSprite.setPositionX( (playerSprite.getHandlerAnimation()->returnAnimationDirectionAxisValue()) * offsetPosition);
    playerSprite.getCollisionBox()->setX( playerSprite.getPosX() - 
                                         ( (playerSprite.getHandlerAnimation()->returnAnimationDirectionAxisValue() )*
                                          playerSprite.getCollisionBox()->getOffset().x ) + 
                                          playerSprite.getCollisionBox()->getOffsetXBasedOnDirection(animationDirection), 
                                          animationDirection );

	if (   playerSprite.getCollisionBox()->getX()/32 > 73 )
	{
	int d = 4;
	}*/

	playerSprite.setNormalPositionX( playerSprite.getSpeedX() );
    playerSprite.getCollisionBox()->setX(playerSprite.getPosX(), playerSprite.getHandlerAnimation()->getAnimationDirection());
    playerSprite.changeStateSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                         std::list<InputMapping::Key>() );
	playerSprite.setSpeedX(0.0f);
	playerSprite.setPlayerMoveInX(false);
    playerSprite.setPlayerMoveInY(false);
    return true;
  }

  if ( !playerSprite.getPlayerMoveBasedInDirection() && !playerSprite.getIsOnGround() && 
        playerSprite.getCurrentState() != GameCoreStates::STILL )
  {
    int animationDirection = playerSprite.getHandlerAnimation()->getAnimationDirection();
		playerSprite.setNormalPositionX( playerSprite.getSpeedX() );
    playerSprite.getCollisionBox()->setX(playerSprite.getPosX(), playerSprite.getHandlerAnimation()->getAnimationDirection());
    /*GLfloat offsetPosition = recalculateSpriteBoxPosition(playerSprite.getCollisionBox()->getX(),
                                                          playerSprite.getCollisionBox()->getOffsetXPosition(animationDirection),
                                                          animationDirection);

    playerSprite.setPositionX( (playerSprite.getHandlerAnimation()->returnAnimationDirectionAxisValue()) * offsetPosition);
    playerSprite.getCollisionBox()->setX( playerSprite.getPosX() - 
                                         ( (playerSprite.getHandlerAnimation()->returnAnimationDirectionAxisValue() )*
                                          playerSprite.getCollisionBox()->getOffset().x ) + 
                                          playerSprite.getCollisionBox()->getOffsetXBasedOnDirection(animationDirection), 
                                          animationDirection );*/
    return true;
  }

    		if ( playerSprite.getCollisionBox()->getX() > 2230 )
		{
		  int d = 4;
		}

  playerSprite.setNormalPositionX( playerSprite.getSpeedX() );

  if ( playerSprite.getHandlerAnimation()->getAnimationDirection() == SpriteData::LEFT )
  {
	  playerSprite.getCollisionBox()->setX(playerSprite.getPosX() +  playerSprite.getCollisionBox()->getOffset().x, 
		  playerSprite.getHandlerAnimation()->getAnimationDirection());
  }
  else
  {
  playerSprite.getCollisionBox()->setX(playerSprite.getPosX(), playerSprite.getHandlerAnimation()->getAnimationDirection());
  }

  		if ( playerSprite.getCollisionBox()->getX() > 2250 )
		{
		  int d = 4;
		}

  return false;
}

bool Collider::checkStatePhysicsModes(Sprite& playerSprite)
{
  int directionAxis = playerSprite.getHandlerAnimation()->returnAnimationDirectionAxisValue();
  std::vector< Vector2f > tempMaxSpeed = playerSprite.getRigidBody().getMaxSpeed();

  if ( playerSprite.getSpeedX()*directionAxis > 0.0f && 
	   playerSprite.getSpeedX()*directionAxis <= tempMaxSpeed.at(GameCoreStates::WALKING).x )
  {
    playerSprite.changeStateSprite(new GameCoreStates::WalkingState(GameCoreStates::WALKING), 0, 
                                   std::list<InputMapping::Key>() );
    playerSprite.setPlayerMoveInX(true);
	return true;
  }

  else if ( playerSprite.getSpeedX()*directionAxis > tempMaxSpeed.at(GameCoreStates::WALKING).x && 
	        playerSprite.getSpeedX()*directionAxis <= tempMaxSpeed.at(GameCoreStates::RUNNING).x )
  {
    playerSprite.changeStateSprite(new GameCoreStates::RunningState(GameCoreStates::RUNNING), GamePhysics::TO_WALKING, 
                                   std::list<InputMapping::Key>() );
    playerSprite.setPlayerMoveInX(true);
	return true;
  }

  else
  {
    playerSprite.changeStateSprite(new GameCoreStates::StillState(GameCoreStates::STILL), 0, 
                                   std::list<InputMapping::Key>() );
	playerSprite.setSpeedX(0.0f);
	playerSprite.setPlayerMoveInX(false);
	return true;
  }

  return false;
}

GLfloat Collider::recalculateSpriteBoxPosition(float initialPosition, float offsetPosition, int direction)
{
  GLfloat startingPosition = (initialPosition + offsetPosition)/32;
  int integerPart = (int)startingPosition;
  GLfloat positionOffsetBox = ( (startingPosition - integerPart)*32 );

  if ( direction == SpriteData::LEFT )
  {
    integerPart += 1;
    positionOffsetBox = ( (integerPart - startingPosition)*32 );
    return positionOffsetBox;
  }
  
  return positionOffsetBox;
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
boost::ptr_vector< Characters::Enemy > Collider::checkAttackCollision(CollisionBox& A, float directionX)
{
  boost::ptr_vector< Characters::Enemy > enemiesCollided;

  for(int i = 0; i == enemies->size(); i++)
  {
    if( checkCollision( A, *enemies->at(i).getSprite()->getCollisionBox(), directionX) )
    {
      enemiesCollided.push_back(&enemies->at(i));
    }
  }
  
  return enemiesCollided;
}*/

/*boost::ptr_vector< Characters::Player > checkEnemiesAttackCollision(CollisionBox& A, float directionX)
{
  boost::ptr_vector< Characters::Player > playersCollided;
  for(int i = 0; i == players->size(); i++)
  {
    if( checkCollision(A, *players->at(i).getCharacterSprite()->getCollisionBox(), directionX) )
    {
      playersCollided.push_back(&players->at(i));
    }
  }
  return playersCollided;
}*/

bool Collider::onTheGround(CollisionSystem::CollisionBox& A, int directionX, int directionY)
{
  int directionPlayer = SpriteData::RIGHT;
  int initialX = 0;

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

    isOnGround = false;

    for(int i = initialX; i < initialX + (int)A.getWidth(); i += 8)
    {
      int x = (int)i/32;
      if ( positionY > 720.0f/32 )
      {
        return false;
      }

      Tile groundTile = layers.at(indexLayer)[positionY][x];

      if( !groundTile.getHasCollision() || (groundTile.getHasCollision() && !groundTile.getIsWalkable()) )
      {
        isOnGround = false;
      }
      else
      {
        isOnGround = true;
        break;
      }
    }
  }

  return isOnGround;
}

bool Collider::checkPositionWithinLevelLength(CollisionSystem::CollisionBox& A, CollisionSystem::DirectionsMove& directionsMove, 
	                                   Vector2f speed, int directionX)
{
  if ( directionX == SpriteData::RIGHT )
  {
	if ( A.getX() + speed.x + A.getWidth() > levelLength )
	{
      directionsMove.setCanMoveRight(false);
      return false;
	}
  }
  else
  {
    if ( A.getX() + speed.x < 0.0f )
    {
	  directionsMove.setCanMoveLeft(false);
	  return false;
	}
  }
  return true;
}