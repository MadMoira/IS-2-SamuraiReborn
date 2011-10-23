
#include "Camera.h"

bool Camera::instanceFlag = false;
Camera* Camera::camera = NULL;

Camera* Camera::getInstance()
{
  if( !instanceFlag )
  {
    camera = new Camera();
    instanceFlag = true;
  }
  return camera;
}

Camera::Camera()
{
  posX = 0;
  speedX = 0;	
  midPoint = 0;
  levelLenght = 6368;
  onePlayer = true;	
  playerOnMidpoint = false;
}

Camera::~Camera()
{
}

void Camera::initCamera()
{
  defaultResolution = SDL_GetVideoInfo();
  midPoint = (GLfloat)defaultResolution->current_w/2;
}

void Camera::moveCamera()
{
  posX += speedX;
  midPoint += speedX;
}

void Camera::setCameraSpeed(GLfloat newSpeedx, GLfloat posx1)
{
  if( checkCamera(posx1, newSpeedx) )
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
  else
  {
    speedX=0;
  }
}

void Camera::setCameraSpeed(GLfloat newSpeedx, GLfloat posx1, GLfloat posx2)
{
  if(checkCamera(posx1, posx2, newSpeedx))
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
  else
  {
    speedX=0;
  }
}

void Camera::renderCamera()
{
  glTranslatef(-posX, 0, 0);
}

void Camera::restartCameraSpeed()
{
  speedX = 0;
}

bool Camera::checkCamera(GLfloat posx1, GLfloat newSpeedx)
{
  if( isPlayerOnMidpoint(posx1) && !isLimit(posX,newSpeedx) )
  {
    return true;
  }	

  return false;
}

bool Camera::checkCamera(GLfloat posx1, GLfloat posx2, GLfloat newSpeedx)
{
  if( ((posx1- midPoint > 0 || posx2 - midPoint > 0) && posX < 4600) || (posX - posx1 > -75 || posX - posx2 > -75) )
  {
    return true;
  }	

  return false;
}

bool Camera::isPlayerOnMidpoint(GLfloat posx)
{
  int distanceToMid = posx - midPoint;
  if(playerOnMidpoint)
  {
    if(abs(distanceToMid) < 300)
	{
      return true;
    }
    else
	{
      playerOnMidpoint = false;
      return false;
    }
  }
  else
  {
    if(abs(distanceToMid) < 75)
	{
      playerOnMidpoint = true;
      return true;
    }
    else
	{
      return false;
    }
  }
}

bool Camera::isLimit(GLfloat position, GLfloat speedX)
{
  if(position + speedX < 0 || position + speedX > levelLenght)
  {
    return true;
  }
  return false;
}