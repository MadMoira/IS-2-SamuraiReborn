
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

bool limitLoop(int sign, int left, int right)
{
  if ( sign == 0 )
  {
	return left <= right;
  }
  else if ( sign == 1 )
  {
	return left >= right;
  }
  else if ( sign == 2 )
  {
	return left < right;
  }
  else if ( sign == 3 )
  {
	return left > right;
  }
}

void Collider::checkTileCollisionY(CollisionSystem::CollisionBox& A, GLfloat* speedX, GLfloat* speedY, int directionX, int directionY, 
                                   CollisionSystem::DirectionsMove& directionsMove, int currentMovement)
{
  int axisY = 1;
  int k = (int)A.getY();
  int sign = 2;
  int leftCondition = k;
  int rightCondition = (int)A.getY() + (int)(*speedY);
  int otherSign = 0;

  if ( directionY == SpriteData::UP )
  {
	 axisY = -1;
	 sign = 3;
  }

  directionsMove.setCanMoveRight(true);
  directionsMove.setCanMoveLeft(true);
  directionsMove.setCanMoveUp(true);
  directionsMove.setCanMoveDown(true);

  GLfloat sy = 0;
  GLfloat initialLoop = sy;

  for (std::string::size_type indexLayer = 0; indexLayer < layers.size(); indexLayer++)
  {
		  initialLoop = 0.0f;
	  sy = 0.0f;
	  k = (int)A.getY();
	  leftCondition = k;
	  sign = 2;
	if ( initialLoop == 0.0f )
	{
			if ( directionY == SpriteData::UP )
		{
		  rightCondition = A.getY() + A.getHeight()/2;
		}
		else if ( directionY == SpriteData::DOWN )
		{
		  rightCondition = A.getY() + A.getHeight();
		}
	}
	for ( k; limitLoop(sign, leftCondition, rightCondition); k += 1*(axisY) )
	{
	  int i = k;
	  int newRightDirection = i;
	  if ( initialLoop == 0.0f )
	  {
		if ( directionY == SpriteData::UP )
		{
		  newRightDirection = A.getY() + A.getHeight()/2;
		}
		else if ( directionY == SpriteData::DOWN )
		{
		  newRightDirection = A.getY() + A.getHeight();
		}
	  }

	  for ( i; limitLoop(0, i, newRightDirection); i += 1 )
	  {
		  int previousTileX = 0;
		  int previousTileY = 0;
		  for ( int j = A.getX(); j < A.getX() + A.getWidth(); j += 2 )
		  {

						int x = (int)j/32;
						int y = (int)i/32;

						if ( x == previousTileX && y == previousTileY )
						{
						  continue;
						}

						previousTileX = x;
						previousTileY = y;

						if ( x > 6400.0f/32 || y > 720.0f/32 )
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
							CollisionSystem::CollisionBox* temp = new CollisionSystem::CollisionBox();
							if ( sy == 0.0f )
							{
								*temp = A;
							}
							else
							{
							   if ( directionY == SpriteData::UP )
							   {
								   temp = new CollisionSystem::CollisionBox(A.getX(), k, A.getWidth(), A.getHeight(), A.getOffset());
							   }
							   else
							   {
							temp = new CollisionSystem::CollisionBox(A.getX(), k - A.getHeight(), A.getWidth(), A.getHeight(), A.getOffset());
							   }
							}


							if ( (int)(newRightDirection/32) == y && y == (int)((temp->getY() + temp->getHeight())/32) )
							{
								if ( !foundTile.getIsWalkable() ) {
									directionsMove.setCanMoveDown(true);
									return;
								}
								else {
									directionsMove.setCanMoveDown(false); }
								
							}
							checkTopBoxCollision(directionsMove, temp->getY()/32, directionY, y);

							delete temp;

		
						  if ( sy == 0.0f && !directionsMove.canMoveYDown)
						  {
							  *speedY = sy;
							  return;
						  }

						  if ( !directionsMove.canMoveYDown )
						  {
						  						  int signo = -1;
						  if ( directionY == SpriteData::DOWN )
						  {
							  signo = 0;
						  }
						  *speedY = sy + -1*(signo);
						  }
		  
						  return;
						}
		  }
	  }

	  	  sy += 1*(axisY);
	  	  if (initialLoop == 0.0f && directionY == SpriteData::DOWN)
	  {
		k = A.getY() + A.getHeight();
		rightCondition = k + (*speedY);
	  }
		  if ( initialLoop == 0.0f && directionY == SpriteData::UP )
		  {
			k = A.getY();
			rightCondition = k + (*speedY);
			sign = 1;
		  }
	  leftCondition = k;
	  initialLoop = sy;
	}
  }
}

void Collider::checkTileCollisionX(CollisionSystem::CollisionBox& A, GLfloat* speedX, GLfloat* speedY, int directionX, int directionY, 
                                   CollisionSystem::DirectionsMove& directionsMove, int currentMovement)
{
  int k = (int)A.getX();
  int sign = 0;
  int leftCondition = k;
  int rightCondition = (int)A.getX() + (int)(*speedX);
  int axisX = 1;

  directionsMove.setCanMoveRight(true);
  directionsMove.setCanMoveLeft(true);
  directionsMove.setCanMoveUp(true);
  directionsMove.setCanMoveDown(true);

  if ( directionX == SpriteData::LEFT )
  {
	axisX = -1;
  }

  GLfloat s = 0;
  GLfloat initialLoop = s;



  for (std::string::size_type indexLayer = 0; indexLayer < layers.size(); indexLayer++)
  {
	  initialLoop = 0.0f;
	  s = 0.0f;
	  k = (int)A.getX();
	  leftCondition = k;
	  sign = 0;

	if ( initialLoop == 0.0f )
	{
	  if ( directionX == SpriteData::RIGHT )
	  {
         rightCondition = A.getX() + A.getWidth();
	  }
	  else if ( directionX == SpriteData::LEFT )
	  {
	     rightCondition = A.getX() + A.getWidth()/2;
	  }
	}

	for ( k; limitLoop(sign, leftCondition, rightCondition); k += 1*(axisX) )
	{
	  int i = k;
	  int newRightDirection = i;
	  if ( initialLoop == 0.0f )
	  {
				  if ( directionX == SpriteData::RIGHT )
		  {
			 newRightDirection = A.getX() + A.getWidth();
		  }
		  else if ( directionX == SpriteData::LEFT )
		  {
			 newRightDirection = A.getX() + A.getWidth()/2;
		  }
	  }

	  for ( i; limitLoop(0, i, newRightDirection); i += 1 )
	  {
		  		  int previousTileX = 0;
		  int previousTileY = 0;
		  for ( int j = A.getY(); j < A.getY() + A.getHeight(); j += 2 )
		  {
			 
						int x = (int)i/32;
						int y = (int)j/32;

						if ( x == previousTileX && y == previousTileY )
						{
						  continue;
						}

						previousTileX = x;
						previousTileY = y;

						if ( x > 6400.0f/32 || y > 720.0f/32 )
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
							CollisionSystem::CollisionBox* temp = new CollisionSystem::CollisionBox();
							if ( s == 0.0f )
							{
								*temp = A;
							}
							else
							{
							temp = new CollisionSystem::CollisionBox(leftCondition, A.getY(), A.getWidth(), A.getHeight(), A.getOffset());
							}
						  checkBottomBoxCollision(*temp, directionsMove, directionX, directionY, x, y, currentMovement);
						  checkBodyBoxCollision(*temp, directionsMove, directionX, directionY, y);

						  delete temp;


						  						    if ( x == 131 && y == 19 && directionX == SpriteData::RIGHT )
							  {
								int d = 4;
							  }

						  if ( (s == 0.0f) && ( (!directionsMove.canMoveXRight && !directionsMove.canMoveXLeft) ||
							  (!directionsMove.canMoveYUp && !directionsMove.canMoveYDown) ) )
						  {
							  *speedX = s;
							  return;
						  }

						  if ( ( (directionsMove.canMoveXRight && directionsMove.canMoveXLeft) &&
							  (directionsMove.canMoveYUp && directionsMove.canMoveYDown) ) )
						  {
							if ( s != 0.0f )
							{
							  *speedX = s;
							}

							return;
						  }

						  int signo = -1;
						  if ( directionX == SpriteData::RIGHT )
						  {
							  signo = 0;
						  }
						  *speedX = s + -1*(signo);
		  
						  return;
						}
			} 
		  
	  }
	  s += 1*(axisX);
	  	  if (initialLoop == 0.0f && directionX == SpriteData::RIGHT)
	  {
		k = A.getX() + A.getWidth();
		rightCondition = k + (*speedX);
	  }
		  if ( initialLoop == 0.0f && directionX == SpriteData::LEFT )
		  {
			k = A.getX();
			rightCondition = k + (*speedX);
			sign = 1;
		  }

	  leftCondition = k;
	  initialLoop = s;

	  
	}
  }
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
        if ( currentPositionX >= (int)(A.getX() + A.getWidth())/32 )
        {
          directionsMove.setCanMoveLeft(true);
          directionsMove.setCanMoveRight(false);
        }
        break;
      }
      case SpriteData::LEFT:
      {
        if ( currentPositionX <= (int)(A.getX())/32 )
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

  if ( playerSprite.getIsOnGround() && ( playerSprite.getCurrentState() == GameCoreStates::FALLING || (
	                                     playerSprite.getCurrentState() == GameCoreStates::JUMPING && playerSprite.getSpeedY() >= -10.0f) ) )
  {
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

  /*playerSprite.setNormalPositionY(playerSprite.getSpeedY());
  playerSprite.getCollisionBox()->setY(playerSprite.getPosY());*/

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
		  if ( playerSprite.getHandlerAnimation()->getAnimationDirection() == SpriteData::LEFT )
  {
	  playerSprite.getCollisionBox()->setX(playerSprite.getPosX() +  playerSprite.getCollisionBox()->getOffset().x, 
		  playerSprite.getHandlerAnimation()->getAnimationDirection());
  }
  else
  {
  playerSprite.getCollisionBox()->setX(playerSprite.getPosX(), playerSprite.getHandlerAnimation()->getAnimationDirection());
  }
                            
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
		  if ( playerSprite.getHandlerAnimation()->getAnimationDirection() == SpriteData::LEFT )
  {
	  playerSprite.getCollisionBox()->setX(playerSprite.getPosX() +  playerSprite.getCollisionBox()->getOffset().x, 
		  playerSprite.getHandlerAnimation()->getAnimationDirection());
  }
  else
  {
  playerSprite.getCollisionBox()->setX(playerSprite.getPosX(), playerSprite.getHandlerAnimation()->getAnimationDirection());
  }
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

		  if ( playerSprite.getHandlerAnimation()->getAnimationDirection() == SpriteData::LEFT )
  {
	  playerSprite.getCollisionBox()->setX(playerSprite.getPosX() +  playerSprite.getCollisionBox()->getOffset().x, 
		  playerSprite.getHandlerAnimation()->getAnimationDirection());
  }
  else
  {
  playerSprite.getCollisionBox()->setX(playerSprite.getPosX(), playerSprite.getHandlerAnimation()->getAnimationDirection());
  }
   // playerSprite.getCollisionBox()->setX(playerSprite.getPosX(), playerSprite.getHandlerAnimation()->getAnimationDirection());
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