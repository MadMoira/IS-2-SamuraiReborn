#include "Camera.h"


Camera::Camera()
{
	posx = posy = 0;
}

void Camera::render()
{
	glTranslatef(-posx, -posy, 0.0f);
}

void Camera::moveCamera(GLfloat dispx, GLfloat dispy)
{
	posx = dispx;
	posy = dispy;
}