#pragma once

#include <windows.h>

#include <string>
#include <vector>
#include <GL/gl.h>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>

#include "Tileset.h"
#include "Layer.h"

enum Levels 
{ 
	LEVELZEROTUTORIAL, 
	LEVELONEJAPAN
};

class Level
{
public:
	Level(void);
	~Level(void);

	void getTileCollision();
	void getTileOfPlayerPosition();
	void loadLevelWithName();
	int loadTMXTileMapFile(std::string filename);

	bool drawLevelMap();

	boost::ptr_vector< Layer > getLayersList() { return layersList; }

private:
	std::string levelName;
	int numberOfEnemies;
	int widthLevelInTiles, heightLevelInTiles;
	boost::ptr_vector< Layer > layersList;
	boost::ptr_vector< Tileset > tilesetList;
};

