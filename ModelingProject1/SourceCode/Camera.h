#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>

class Camera
{
  public:
   static Camera* getInstance();

   Camera();
   ~Camera();

   void initCamera();

   void moveCamera();
	
   void renderCamera();

   bool checkCamera(GLfloat posx1, GLfloat newSpeedx);
   bool checkCamera(GLfloat posx1, GLfloat posx2, GLfloat newSpeedx);
	
   void setCameraSpeed(GLfloat newSpeedx, GLfloat posx1);
   void setCameraSpeed(GLfloat newSpeedx, GLfloat posx1, GLfloat posx2);
   void restartCameraSpeed();

   GLfloat getCameraPosition() { return posX; }

   GLfloat getCameraSpeed() {return speedX;}

   bool isPlayerOnMidpoint(GLfloat posX);
   bool isLimit(GLfloat position, GLfloat speedX);

  private:
	static bool instanceFlag;
	static Camera* camera;
	GLfloat posX;	
	GLfloat speedX;
	GLfloat midPoint;
	GLfloat levelLenght;
	bool onePlayer;
	bool playerOnMidpoint;
	const SDL_VideoInfo* defaultResolution;
};