#include "Tileset.h"


Tileset::Tileset(void)
{
	ID = heightTile = widthTile = numberOfTiles = 0;
	filename = "";
}


Tileset::~Tileset(void)
{
	listCollisionTiles.clear();
	glDeleteTextures(1, &texture);
}
