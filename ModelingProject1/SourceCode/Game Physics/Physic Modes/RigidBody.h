#pragma once

#include "PhysicsCore.h"

namespace GamePhysics
{
  class RigidBody : public PhysicsCore
  {
    public:
     RigidBody(int mode);
     ~RigidBody(void);

     void initializeNaturalPhysicsForces(float forceOne, float forceTwo);
     void applyNaturalPhysicForces(int currentMovement, GLfloat* speedX, GLfloat* speedY, int playerState, int direction, 
		                           int previousState);
	 void initializeSpeedVectors(std::vector< Vector2f > maxSpeed);

	 void setAccelerationState(int state) { accState = (AccelerationState)state; }

    private:
     float gravityValue;
     float accelerationXValue;

	 AccelerationState accState;

	 std::vector< Vector2f > maxSpeed;

     void parabolicShot(GLfloat* yVelocity, int playerState);
	 void acceleratePlayer(GLfloat* xVelocity, int playerState, int previousState, int directionX);
  };
}
