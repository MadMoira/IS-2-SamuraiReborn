#pragma once

#include <windows.h>

#include <string>
#include <vector>
#include <GL/gl.h>

#include "Tileset.h"

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

private:
	std::string levelName;
	int numberOfEnemies;
	std::vector<int> listCollisionTiles;
	//boost::ptr_vector< Tileset > tilesetList;
	/*Implement the map with smart pointers*/
};

