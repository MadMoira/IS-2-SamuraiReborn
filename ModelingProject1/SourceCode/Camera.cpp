
#include "Camera.h"

Camera::Camera()
{
  posX = 0;
  speedX = 0;	
  midPoint = 0;
  onePlayer = true;	
}

Camera::~Camera()
{
}

void Camera::initCamera()
{
  defaultResolution = SDL_GetVideoInfo();
  midPoint = (GLfloat)defaultResolution->current_w/2;
}

void Camera::moveCamera(GLfloat posx1)
{
  if ( checkCamera(posx1) )
  {
    posX += speedX;
    midPoint += speedX;
  }

  else
  {
    speedX = 0;
  }
}

void Camera::moveCamera(GLfloat posx1, GLfloat posx2)
{
  if( checkCamera(posx1, posx2) )
  {
    posX += speedX;
    midPoint += speedX;
  }

  else
  {
    speedX = 0;
  }
}

void Camera::renderCamera()
{
  glTranslatef(-posX, 0, 0);
}

void Camera::setCameraSpeed(GLfloat newSpeedx)
{
  if( onePlayer )
  {
    speedX += newSpeedx;
  }

  else
  {
    speedX += newSpeedx/2;
  }
}

void Camera::restartCameraSpeed()
{
  speedX = 0;
}

bool Camera::checkCamera(GLfloat posx1)
{
  if( (posx1 - midPoint > 0 && posX < 4600) || posX - posx1 > -75)
  {
    return true;
  }	

  return false;
}

bool Camera::checkCamera(GLfloat posx1, GLfloat posx2)
{
  if( ((posx1- midPoint > 0 || posx2 - midPoint > 0) && posX < 4600) || (posX - posx1 > -75 || posx - posx2 > -75) )
  {
    return true;
  }	

  return false;
}

