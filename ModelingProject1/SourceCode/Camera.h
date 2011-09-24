#pragma once
#include <SDL\SDL.h>
#include <SDL\SDL_opengl.h>

struct V2Cam{

	GLfloat movx, movy;
};

class Camera{

public:

	Camera();
	~Camera();
	void render();
	void moveCamera(GLfloat dispx, GLfloat dispy);

private:

	GLfloat posx, posy;

};