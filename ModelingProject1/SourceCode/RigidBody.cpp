
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
  groundFrictionValue = forceTwo;
}

void GamePhysics::RigidBody::applyNaturalPhysicForces(int currentMovement, GLfloat* speedX, GLfloat* speedY, 
                                                      int playerState, int direction)
{
  switch(currentMovement)
  {
    case GamePhysics::X:
    {
      groundFriction(speedX, playerState, direction);
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

void GamePhysics::RigidBody::groundFriction(GLfloat* xVelocity, int playerState, int direction)
{
  int axisValue = 1;

  if ( direction == SpriteData::LEFT )
  {
    axisValue = -1;
  }

  if( playerState == GameCoreStates::STOPPING )
  {
    *xVelocity -= (axisValue)*groundFrictionValue;
    if( *xVelocity == 0.0f )
    {
      *xVelocity = 0.0f;
    }
  }
}
