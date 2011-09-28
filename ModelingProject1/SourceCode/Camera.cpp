#include "Camera.h"

Camera::Camera(){
	posx = posy = 0;
	speedx = 0;
}

Camera::~Camera(){

}

void Camera::moveCamera(){
	posx += speedx;
}

void Camera::renderCamera(){
	glTranslatef(-posx, 0, 0);
}

void Camera::setCameraSpeed(GLfloat newSpeedx){
	speedx = newSpeedx;
}

bool Camera::checkMidCam(GLfloat posxP1, GLfloat posxP2){
	return true;
}

