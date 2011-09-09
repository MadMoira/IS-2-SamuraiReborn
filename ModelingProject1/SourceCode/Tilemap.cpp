#include "Tilemap.h"


Tilemap::Tilemap(std::string name, int widthInTiles, int heightInTiles)
{
	nameLayer = name;
	widthLevelInTiles = widthInTiles;
	heightLevelInTiles = heightInTiles;

	layerMap.resize(heightLevelInTiles);
	
	for (int i = 0; i < heightLevelInTiles; i++)
	{
		layerMap[i].resize(widthLevelInTiles);
	}
}

Tilemap::~Tilemap(void)
{
	layerMap.clear();
}
