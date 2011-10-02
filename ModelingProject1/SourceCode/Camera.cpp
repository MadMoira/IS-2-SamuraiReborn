#include "Camera.h"

Camera::Camera(){
	posx = posy = 0;
	speedx = 0;	
	midPoint = 0;
}

Camera::~Camera(){
}

void Camera::initCamera(){
	defaultResolution = SDL_GetVideoInfo();
	midPoint = defaultResolution->current_w/2;
}

void Camera::moveCamera(GLfloat posxP1, GLfloat posxP2, GLfloat widthP1, GLfloat widthP2){	
	
	if (checkMidCam(posxP1, posxP2, widthP1, widthP2)){
		posx += speedx;
		midPoint += speedx;
	}
	else{
		speedx = 0;
	}

}

void Camera::renderCamera(){
	glTranslatef(-posx, 0, 0);
}

void Camera::setCameraSpeed(GLfloat newSpeedx){
	speedx = newSpeedx;
}

bool Camera::checkMidCam(GLfloat posxP1, GLfloat posxP2, GLfloat widthP1, GLfloat widthP2){	

	std::cout << "panda posx: " << posxP1 << std::endl;
	std::cout << "meerkat posx: " << posxP2 << std::endl;
	std::cout << "midcam posx: " << midPoint << std::endl;
	std::cout << "diff: " << (posxP1 - midPoint > 0) << std::endl; 
	std::cout << std::endl;
	
	if(/*(posxP1 - posxP2) <= defaultResolution->current_w/2 &&*/ ((posxP1+widthP1 )- midPoint > 0 || (posxP2+widthP2) - midPoint > 0)){
		return true;
	}	

	return false;

}

