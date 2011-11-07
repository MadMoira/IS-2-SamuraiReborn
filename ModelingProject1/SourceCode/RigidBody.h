#pragma once

#include "PhysicsCore.h"

namespace GamePhysics
{
  class RigidBody : public PhysicsCore
  {
    public:
	 RigidBody(int mode);
	 ~RigidBody(void);

	 void initializeNaturalPhysicsForces(float forceOne);
	 void applyNaturalPhysicForces(GLfloat* speedY, int playerState);

    private:
	 float gravityValue;

	 void parabolicShot(GLfloat* yVelocity, int playerState);
  };
}
