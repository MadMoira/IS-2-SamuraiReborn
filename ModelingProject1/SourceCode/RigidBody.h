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
     void applyNaturalPhysicForces(int currentMovement, GLfloat* speedX, GLfloat* speedY, int playerState, int direction);

    private:
     float gravityValue;
     float groundFrictionValue;

     void parabolicShot(GLfloat* yVelocity, int playerState);
     void groundFriction(GLfloat* xVelocity, int playerState, int direction);
  };
}
