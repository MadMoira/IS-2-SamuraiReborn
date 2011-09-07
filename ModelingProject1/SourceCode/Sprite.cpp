#include "Sprite.h"


Sprite::Sprite(void)
{
}


Sprite::~Sprite(void)
{
	glDeleteTextures(1, &texture);
}
