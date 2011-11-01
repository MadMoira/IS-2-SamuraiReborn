#pragma once

#include <windows.h>
#include <GL/gl.h>

struct Vector2f
{
  GLfloat x, y;

  Vector2f(GLfloat pointX, GLfloat pointY) 
  {
    x = pointX;	
    y = pointY; 
  }

  Vector2f()
  {
    x = y = 0;
  }
};
