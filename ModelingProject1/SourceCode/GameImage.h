#pragma once

#include <windows.h>
#include <gl\GL.h>

#include <string>

#include "Vector.h"

namespace Image
{
  class GameImage
  {
   public:
    GameImage(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, std::string filename);
    GameImage(){};
    ~GameImage(void);

    GLuint getTexture() { return texture; }

    Vector2f getPosition() { return position; }
    void setPosition(GLfloat x, GLfloat y) { position = Vector2f(x, y); }

    Vector2f getOffset() { return offset; }

    Vector2f getTexturePosition() { return texturePosition; }

   private:
    GLuint texture;
    Vector2f position;
    Vector2f offset;
    Vector2f texturePosition;
  };
}