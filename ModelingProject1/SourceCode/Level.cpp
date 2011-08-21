#include "Level.h"


Level::Level(void)
{
	tiles = new Tileset();
}


Level::~Level(void)
{
	delete tiles;
}
