#include "PhysicsCore.h"

bool GamePhysics::PhysicsCore::instanceFlag = false;
GamePhysics::PhysicsCore* GamePhysics::PhysicsCore::physics = NULL;

GamePhysics::PhysicsCore* GamePhysics::PhysicsCore::getInstance()
{
  if( !instanceFlag )
  {
    physics = new PhysicsCore();
    instanceFlag = true;
  }
  return physics;
}

GamePhysics::PhysicsCore::PhysicsCore()
{
}

GamePhysics::PhysicsCore::PhysicsCore(float gravityVal)
{
  this->gravityVal = gravityVal;
}

GamePhysics::PhysicsCore::~PhysicsCore(void)
{
}

void GamePhysics::PhysicsCore::initializePhysicValues(float gravity)
{
  gravityVal = gravity;
}

void GamePhysics::PhysicsCore::parabolicShot(GLfloat* yVelocity, int playerState)
{
  if( playerState == 2 || playerState == 4 || playerState == 6 )
  {
    *yVelocity -= gravityVal;
	return;
  }
  *yVelocity = 0.0f;
}

void GamePhysics::PhysicsCore::physicManager(GLfloat* speedY, int state, int playerState)
{
  switch(state)
  {
   case GamePhysics::PARABOLIC:
   {
    parabolicShot(speedY, playerState);
    break;
   }
  }
}
