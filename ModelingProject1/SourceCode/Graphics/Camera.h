#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include "Player.h"

class Camera
{
  public:
   static Camera* getInstance();

   Camera();
   ~Camera();

   void initCamera();
    
   void renderCamera();

   bool checkCamera(boost::ptr_vector<Characters::Player>* players);
   void resetCamera(GLfloat level, GLfloat spawningPoint);
    
   void updateCamera(boost::ptr_vector<Characters::Player>* players);

   GLfloat getCameraPosition() { return posX; }
   void setCameraSpeed(GLfloat newSpeed) { speedX = newSpeed; }
   GLfloat getCameraSpeed() { return speedX; }

   bool isOnMidpoint(GLfloat posX);
   bool isLimit(GLfloat position, GLfloat speedX);

  private:
    static bool instanceFlag;
    static Camera* camera;
    GLfloat posX;	
    GLfloat speedX;
    GLfloat midPoint;
    GLfloat interactionPoint;
    GLfloat levelLenght;
    bool onMidpoint;
    const SDL_VideoInfo* defaultResolution;
};