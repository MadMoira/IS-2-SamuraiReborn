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
    
     virtual void initializeNaturalPhysicsForces(float forceOne, float forceTwo) = 0;
     virtual void applyNaturalPhysicForces(int currentMovement, GLfloat* speedX, GLfloat* speedY, 
                                           int playerState, int direction) = 0;

    protected:
     PhysicModes nameMode;
  };
}
