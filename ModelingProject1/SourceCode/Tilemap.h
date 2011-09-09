#pragma once

#include <string>
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>

class Tilemap
{
public:
	Tilemap(std::string name, int widthLayer, int heightLayer);
	~Tilemap(void);
	
	std::vector< std::vector <int> > getLayerMap() { return layerMap; } ;
	void setLayerMap(std::vector< std::vector <int> > map) { layerMap = map; };

	int getWidthLevelInTiles() { return widthLevelInTiles; }
	void setWidthLevelInTiles(int width) { widthLevelInTiles = width; }

	int getHeightLevelInTiles() { return heightLevelInTiles; }
	void setHeightLevelInTiles(int height) { heightLevelInTiles = height; }

private:
	std::string nameLayer;
	std::vector< std::vector <int> > layerMap;
	int widthLevelInTiles, heightLevelInTiles;
};

