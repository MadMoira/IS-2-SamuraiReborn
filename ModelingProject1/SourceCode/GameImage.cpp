#include "GameImage.h"

#include "GameRender.h"

Image::GameImage::GameImage(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, 
	                        std::string filename)
{
  position = imagePosition;
  offset = imageOffset;
  this->texturePosition = texturePosition;
  texture = GameRender::loadTexture(filename);
}

Image::GameImage::~GameImage(void)
{
  glDeleteTextures(1, &texture);
}
