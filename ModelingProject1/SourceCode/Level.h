#pragma once

#include <windows.h>

#include <GL/gl.h>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/lexical_cast.hpp>

#include "Vector.h"

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
	Level(Levels id);
	~Level(void);

	int loadTMXTileMapFile(std::string filename);

	bool drawLevelMap();

	boost::ptr_vector< Layer > getLayersList() { return layersList; }
	void addLayerToList(std::string name, GLfloat widthLayer, GLfloat heightLayer, Vector2f vel, 
				 GLfloat constantX, bool hasRepetition);
	void scrollBackgroundLayers();
	void checkLayersSpeed(GLfloat speedX);

	boost::ptr_vector< Tilemap > getTilemapList() { return tilemapList; }
	void scrollTilemap();
	void checkTilemapsSpeed(GLfloat speedX);

private:
	Levels IDLevel;
	boost::ptr_vector< Layer > layersList;
	boost::ptr_vector< Tilemap > tilemapList;
};

