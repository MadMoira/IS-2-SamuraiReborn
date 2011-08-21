#pragma once

#include <windows.h>

#include <string>
#include <vector>
#include <GL/gl.h>

#include "Tileset.h"

using namespace std;

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
	void loadTMXTileMapFile();

private:
	string levelName;
	int numberOfEnemies;
	vector<int> listCollisionTiles;
	Tileset *tiles;
	/*Implement the map with smart pointers*/
};

