#pragma once

#include <windows.h>
#include <GL/gl.h>

#include "PhysicStates.h"
#include "Vector.h"

namespace GamePhysics
{
  class PhysicsCore
  {
    public:
     static PhysicsCore* getInstance();
	 PhysicsCore(float gravityVal);
	 PhysicsCore();
	 ~PhysicsCore(void);
	
	 void initializePhysicValues(float gravity);
	 void physicManager(GLfloat* speedY, int state, int playerState);

    private:
     static bool instanceFlag;
	 static PhysicsCore* physics;
	 float gravityVal;
	 void parabolicShot(GLfloat* speedY, int playerState); 
  };
}
