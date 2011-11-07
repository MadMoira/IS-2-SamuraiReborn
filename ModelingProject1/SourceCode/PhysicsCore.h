#pragma once

#include <windows.h>
#include <GL/gl.h>

#include "PhysicModes.h"
#include "Vector.h"

namespace GamePhysics
{
  class PhysicsCore
  {
    public:
	 PhysicsCore(int mode);
	 ~PhysicsCore(void);
	
	 virtual void initializeNaturalPhysicsForces(float forceOne) = 0;
	 virtual void applyNaturalPhysicForces(GLfloat* speedY, int playerState) = 0;

    protected:
	 PhysicModes nameMode;
  };
}
