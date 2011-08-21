#include "Tileset.h"


Tileset::Tileset(void)
{
}


Tileset::~Tileset(void)
{
	glDeleteTextures(1, &texture);
}
