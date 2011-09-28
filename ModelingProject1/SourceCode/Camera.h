#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>

class Camera{

public:

	Camera();
	~Camera();
	void moveCamera();
	void renderCamera();

	bool checkMidCam(GLfloat posxP1, GLfloat posxP2);

	void setCameraSpeed(GLfloat newSpeedx);
	GLfloat getCameraSpeed() {return speedx;};

private:

	GLfloat posx, posy;
	GLfloat speedx;

};