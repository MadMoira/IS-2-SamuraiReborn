#pragma once

#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>

class Camera{

public:

	Camera();
	~Camera();

	static Camera* getInstance();

	void initCamera();

	void moveCamera();
	
	void renderCamera();

	bool checkCam(GLfloat posx1,GLfloat newSpeedx);
	bool checkCam(GLfloat posx1, GLfloat posx2, GLfloat newSpeedx);
	
	void setCameraSpeed(GLfloat newSpeedx, GLfloat posx1);
	void setCameraSpeed(GLfloat newSpeedx, GLfloat posx1, GLfloat posx2);
	void restartCameraSpeed();

	GLfloat getCameraPosition() { return posx; }

	GLfloat getCameraSpeed() {return speedx;};
	bool getOnePlayer() {return onePlayer;};
	bool isPlayerOnMidpoint(GLfloat posX);
	bool isLimit(GLfloat position, GLfloat speedX);

private:
	static bool instanceFlag;
	static Camera* camera;
	GLfloat levelLenght;
	GLfloat posx;	
	GLfloat speedx;
	GLfloat midPoint;
	bool onePlayer;
	bool playerOnMidpoint;
	const SDL_VideoInfo* defaultResolution;
};