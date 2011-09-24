#pragma once

#include <windows.h>
#include <GL/gl.h>

#include <vector>
#include <exception>

#include <boost/ptr_container/ptr_vector.hpp>

#include "GameRender.h"
#include "Tileset.h"

class Tilemap
{
public:
	Tilemap(std::string name, int widthInTiles, int heightInTiles);
	~Tilemap(void);

	bool drawTilemap(GLfloat sizeTile, int indexTileset);
	
	std::vector< std::vector <int> > getLayerMap() { return layerMap; } ;
	void setLayerMap(std::vector< std::vector <int> > map) { layerMap = map; };

	int getWidthLevelInTiles() { return widthLevelInTiles; }
	void setWidthLevelInTiles(int width) { widthLevelInTiles = width; }

	int getHeightLevelInTiles() { return heightLevelInTiles; }
	void setHeightLevelInTiles(int height) { heightLevelInTiles = height; }

	boost::ptr_vector< Tileset > getTilesetList() { return tilesetList; }
	void addTileset(int id, std::string name, GLfloat widthTile, GLfloat heightTile, GLfloat imageWidth, GLfloat imageHeight, 
					int size);

private:
	std::string nameLayer;
	std::vector< std::vector <int> > layerMap;
	int widthLevelInTiles, heightLevelInTiles;
	boost::ptr_vector< Tileset > tilesetList;
	GLfloat offsetX, offsetY;
};

