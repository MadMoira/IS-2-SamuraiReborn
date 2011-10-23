
#include "Camera.h"

Camera::Camera()
{
  posx = 0;
  speedx = 0;	
  midPoint = 0;
  levelLenght=2000;
  onePlayer = true;	
  playerOnMidpoint=false;
}

Camera::~Camera()
{
}

bool Camera::instanceFlag=false;
Camera* Camera::camera=NULL;

Camera* Camera::getInstance(){
	if( !instanceFlag )
	  {
		camera = new Camera();
		instanceFlag = true;
	  }
	  return camera;
}

void Camera::initCamera()
{
  defaultResolution = SDL_GetVideoInfo();
  midPoint = (GLfloat)defaultResolution->current_w/2;
}

void Camera::moveCamera()
{
    posx += speedx;
    midPoint += speedx;
}

void Camera::renderCamera()
{
  glTranslatef(-posx, 0, 0);
}

void Camera::setCameraSpeed(GLfloat newSpeedx, GLfloat posx1)
{
	 if(checkCam(posx1,newSpeedx))
	 {
		if( onePlayer )
		{
		speedx += newSpeedx;
		}
		else
		{
		speedx += newSpeedx/2;
		}
	 }
	 else{
		 speedx=0;
	 }
}

void Camera::setCameraSpeed(GLfloat newSpeedx, GLfloat posx1, GLfloat posx2)
{
	 if(checkCam(posx1, posx2))
	 {
		if( onePlayer )
		{
		speedx += newSpeedx;
		}
		else
		{
		speedx += newSpeedx/2;
		}
	 }
	 else{
		 speedx=0;
	 }
}

void Camera::restartCameraSpeed()
{
  speedx = 0;
}

bool Camera::checkCam(GLfloat posx1, GLfloat newSpeedx)
{	
  if( isPlayerOnMidpoint(posx1) && (!isLimit(posx,newSpeedx)&&!isLimit(posx+(GLfloat)defaultResolution->current_w,newSpeedx)))
  {
    return true;
  }	

  return false;
}

bool Camera::checkCam(GLfloat posx1, GLfloat posx2, GLfloat newSpeedx)
{
  if( ((posx1- midPoint > 0 || posx2 - midPoint > 0) && posx < 4600) || (posx - posx1 > -75 || posx - posx2 > -75) )
  {
    return true;
  }	

  return false;
}

bool Camera::isPlayerOnMidpoint(GLfloat posX){
	int distanceToMid = posX- midPoint;
	if(playerOnMidpoint){
		if(abs(distanceToMid) <250){
			return true;
		}
		else{
			playerOnMidpoint=false;
			return false;
		}
	}
	else{
		if(abs(distanceToMid) < 40	){
			playerOnMidpoint=true;
			return true;
		}
		else{
			return false;
		}
	}
}

bool Camera::isLimit(GLfloat position, GLfloat speedX){
	if(position+speedX<0 || position+speedX>levelLenght){
		return true;
	}
	return false;
}