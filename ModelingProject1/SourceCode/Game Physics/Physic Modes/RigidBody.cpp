
#include "RigidBody.h"

#include "SpriteDataConstants.h"
#include "PlayerSpriteStates.h"

GamePhysics::RigidBody::RigidBody(int mode) : PhysicsCore( mode )
{
  nameMode = (GamePhysics::PhysicModes)mode;
}

GamePhysics::RigidBody::~RigidBody(void)
{
}

void GamePhysics::RigidBody::initializeNaturalPhysicsForces(float forceOne, float forceTwo)
{
  gravityValue = forceOne;
  accelerationXValue = forceTwo;

  accState = GamePhysics::NO_ACCELERATE;
}

void GamePhysics::RigidBody::initializeSpeedVectors(std::vector< Vector2f > maxSpeed)
{
  this->maxSpeed = maxSpeed;
}

void GamePhysics::RigidBody::applyNaturalPhysicForces(int currentMovement, GLfloat* speedX, GLfloat* speedY, 
                                                      int playerState, int direction, int previousState)
{
  switch(currentMovement)
  {
    case GamePhysics::X:
    {
	  acceleratePlayer(speedX, playerState, previousState, direction);
      break;
    }
    case GamePhysics::Y:
    {
      parabolicShot(speedY, playerState);
      break;
    }
  }
}

void GamePhysics::RigidBody::parabolicShot(GLfloat* yVelocity, int playerState)
{
  if( playerState == GameCoreStates::JUMPING || playerState == GameCoreStates::DOUBLE_JUMP || 
      playerState == GameCoreStates::FALLING )
  {
    *yVelocity -= gravityValue;
    if ( *yVelocity >= 30.0f )
    {
      *yVelocity = 30.0f;
    }
    return;
  }
  *yVelocity = 0.0f;
}

void GamePhysics::RigidBody::acceleratePlayer(GLfloat* xVelocity, int playerState, int previousState, int directionX)
{
  switch( accState )
  {
  case ACCELERATE:
	  {
	  }
  case DECELERATE:
	  {
	  }
  }
	if ( playerState == GameCoreStates::WALKING && accState == 1 )
	{
  *xVelocity += accelerationXValue;
  if ( *xVelocity >= maxSpeed.at(playerState).x )
  {
	*xVelocity = maxSpeed.at(playerState).x ;
  }
	}


		if ( playerState == GameCoreStates::WALKING && accState == 2 )
	{
  *xVelocity -= accelerationXValue;
  if ( *xVelocity <= 0.0f )
  {
	*xVelocity = 0.0f;
  }
	}

		if ( playerState == GameCoreStates::RUNNING && accState == 1)
	{
  *xVelocity += accelerationXValue;
  if ( *xVelocity >= maxSpeed.at(playerState).x  )
  {
	*xVelocity = maxSpeed.at(playerState).x ;
  }
	}

				if ( playerState == GameCoreStates::RUNNING && accState == 2 )
	{
  *xVelocity -= accelerationXValue;
  if ( *xVelocity <= 0.0f )
  {
	*xVelocity = 0.0f;
  }
	}

				if ( playerState == GameCoreStates::JUMPING && accState == 1 && previousState == GameCoreStates::WALKING)
	{
  *xVelocity += accelerationXValue;
  if ( *xVelocity >= maxSpeed.at(previousState).x  )
  {
	*xVelocity = maxSpeed.at(previousState).x ;
  }
	}

								if ( playerState == GameCoreStates::JUMPING && accState == 1 && previousState == GameCoreStates::RUNNING)
	{
  *xVelocity += accelerationXValue;
  if ( *xVelocity >= maxSpeed.at(previousState).x  )
  {
	*xVelocity = maxSpeed.at(previousState).x ;
  }
	}

												if ( playerState == GameCoreStates::DOUBLE_JUMP && accState == 1 && previousState == GameCoreStates::WALKING)
	{
  *xVelocity += accelerationXValue;
  if ( *xVelocity >= maxSpeed.at(previousState).x)
  {
	*xVelocity = maxSpeed.at(previousState).x;
  }
	}

								if ( playerState == GameCoreStates::DOUBLE_JUMP && accState == 1 && previousState == GameCoreStates::RUNNING)
	{
  *xVelocity += accelerationXValue;
  if ( *xVelocity >= maxSpeed.at(previousState).x )
  {
	*xVelocity = maxSpeed.at(previousState).x;
  }
	}

				if ( playerState == GameCoreStates::STILL)
	{
  *xVelocity -= accelerationXValue;
  if ( *xVelocity <= 0.0f )
  {
	*xVelocity = 0.0f;
  }
	}
}