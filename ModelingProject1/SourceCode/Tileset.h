#pragma once

#include <windows.h>

#include <string>
#include <GL/gl.h>

class Tileset
{
public:
	Tileset(void);
	~Tileset(void);

	void loadTexture();
	void getTileWithID();

	void setFilename(std::string name) { filename = name; }

	void setHeightTile(int height) { heightTile = height; }

	void setWidthTile(int width) { widthTile = width; }

	void setNumberOfTiles(int number) { numberOfTiles = number; }

private:
	std::string filename;
	GLuint texture;
	int ID;
	int heightTile, widthTile;
	int numberOfTiles;
};

