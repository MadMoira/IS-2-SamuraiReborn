#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>

class Camera
{
  public:
   Camera();
   ~Camera();

   void initCamera();

   void moveCamera(GLfloat posx1);
   void moveCamera(GLfloat posx1, GLfloat posx2);
	
   void renderCamera();

   bool checkCamera(GLfloat posx1);
   bool checkCamera(GLfloat posx1, GLfloat posx2);

   void setCameraSpeed(GLfloat newSpeedx);
   void restartCameraSpeed();

   GLfloat getCameraPosition() { return posX; }

   GLfloat getCameraSpeed() {return speedX;};

   bool getOnePlayer() {return onePlayer;};

  private:
   GLfloat posX;	
   GLfloat speedX;
   GLfloat midPoint;
   bool onePlayer;
   const SDL_VideoInfo* defaultResolution;
};