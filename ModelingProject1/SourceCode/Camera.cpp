
#include "Camera.h"

#define GRAB_CAMERA_RANGE 40
#define RELEASE_CAMERA_RANGE 300

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
  onMidpoint=false;
}

Camera::~Camera()
{
}

void Camera::initCamera()
{
  defaultResolution = SDL_GetVideoInfo();
  midPoint = (GLfloat)defaultResolution->current_w/2;
}

void Camera::renderCamera()
{
  glTranslatef(-posX, 0, 0);
}

void Camera::updateCamera(boost::ptr_vector<Player>* players)
{ 	
	if( players->size()==1 )
	{
		GLfloat playerPosition=players->at(0).getPlayerSprite()->getPosX();
		speedX=playerPosition-interactionPoint;
		interactionPoint=playerPosition;
	}
	else if(players->size()>1)
	{
		GLfloat minPosition=std::numeric_limits<float>::max();
		GLfloat maxPosition=-std::numeric_limits<float>::max();
		
		for(unsigned i=0;i<players->size();i++){
			if(players->at(i).getPlayerSprite()->getPosX()>maxPosition){
				maxPosition=players->at(i).getPlayerSprite()->getPosX();
			}
			else if(players->at(i).getPlayerSprite()->getPosX()<minPosition){
				minPosition=players->at(i).getPlayerSprite()->getPosX();
			}
		}
		speedX=((maxPosition-minPosition)/2)-interactionPoint;
		interactionPoint=(maxPosition-minPosition)/2;
	}
	if( !checkCamera(players) || !isOnMidpoint(interactionPoint) )
	{
		speedX=0;
	}
	else
	{
		midPoint+=speedX;
		posX+=speedX;
	}
}

bool Camera::checkCamera(boost::ptr_vector<Player>* players)
{	
	for(unsigned i=0;i<players->size();i++){
		if( isLimit(posX,players->at(i).getPlayerSprite()->getSpeedX()) ||
			isLimit(posX + (GLfloat)defaultResolution->current_w, players->at(i).getPlayerSprite()->getSpeedX()))
		  {
			return false;
		  }	
	}
  return true;
}


void Camera::resetCamera(GLfloat level, GLfloat spawningPoint)
{
  posX = 0;
  speedX = 0;	
  levelLenght = level;
  onMidpoint = false;
  interactionPoint=spawningPoint;
}

bool Camera::isOnMidpoint(GLfloat posX)
{
  int distanceToMid = abs((int)posX - (int)midPoint);
  if( onMidpoint )
  {
    if( distanceToMid < RELEASE_CAMERA_RANGE )
	{
      return true;
    }
    else
	{
      onMidpoint = false;
      return false;
    }
  }
  else
  {
	  if( distanceToMid < GRAB_CAMERA_RANGE )
	{
      onMidpoint = true;
      return true;
    }
    else
	{
      return false;
    }
  }
}

bool Camera::isLimit(GLfloat position, GLfloat speed)
{
  if(position + speed < -15 || position + speed > levelLenght)
  {
    return true;
  }
  return false;
}