
#include "RigidBody.h"

#include "PlayerSpriteStates.h"

GamePhysics::RigidBody::RigidBody(int mode) : PhysicsCore( mode )
{
  nameMode = (GamePhysics::PhysicModes)mode;
}

GamePhysics::RigidBody::~RigidBody(void)
{
}

void GamePhysics::RigidBody::initializeNaturalPhysicsForces(float forceOne)
{
  gravityValue = forceOne;
}

void GamePhysics::RigidBody::applyNaturalPhysicForces(GLfloat* speedY, int playerState)
{
  parabolicShot(speedY, playerState);
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
