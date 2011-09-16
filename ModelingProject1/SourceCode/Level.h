#pragma once

#include <windows.h>

#include <string>
#include <vector>
#include <GL/gl.h>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>

#include "Tileset.h"
#include "Layer.h"
#include "Tilemap.h"

#include "GameCore.h"

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

	int loadTMXTileMapFile(std::string filename);

	bool drawLevelMap();

	boost::ptr_vector< Layer > getLayersList() { return layersList; }
	void addLayerToList(std::string name, GLfloat widthLayer, GLfloat heightLayer, GLfloat velX, GLfloat velY);
	void scrollBackgroundLayers();

	boost::ptr_vector< Tilemap > getTilemapList() { return tilemapList; }

private:
	std::string levelName;
	int numberOfEnemies;
	boost::ptr_vector< Layer > layersList;
	boost::ptr_vector< Tilemap > tilemapList;
};

