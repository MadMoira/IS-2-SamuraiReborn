#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>
#include <iostream>

class Camera{

public:

	Camera();
	~Camera();

	void initCamera();

	void moveCamera(GLfloat posxP1, GLfloat posxP2, GLfloat widthP1, GLfloat widthP2);
	void renderCamera();

	bool checkMidCam(GLfloat posxP1, GLfloat posxP2, GLfloat widthP1, GLfloat widthP2);

	void setCameraSpeed(GLfloat newSpeedx);
	GLfloat getCameraSpeed() {return speedx;};

private:

	GLfloat posx, posy;
	GLfloat speedx;
	GLfloat midPoint;
	const SDL_VideoInfo* defaultResolution;
	
};