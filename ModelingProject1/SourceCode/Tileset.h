#pragma once

#include <windows.h>

#include <map>
#include <string>
#include <GL/gl.h>

class Tileset
{
public:
	Tileset(void);
	~Tileset(void);

	void loadTexture();
	void getTileWithID();

	std::map< int, std::string > getListCollisionTiles() { return listCollisionTiles; }
	void setListCollisionTiles(std::map< int, std::string > list) { listCollisionTiles = list; }

	void setFilename(std::string name) { filename = name; }

	void setHeightTile(int height) { heightTile = height; }

	void setWidthTile(int width) { widthTile = width; }

	void setNumberOfTiles(int number) { numberOfTiles = number; }

	void setID(int id) { ID = id; }

private:
	std::string filename;
	GLuint texture;
	int ID;
	int heightTile, widthTile;
	int numberOfTiles;
	std::map< int, std::string > listCollisionTiles;
};

