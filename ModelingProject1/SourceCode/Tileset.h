#pragma once

#include <windows.h>

#include <string>
#include <GL/gl.h>

using namespace std;

class Tileset
{
public:
	Tileset(void);
	~Tileset(void);

	void loadTexture();
	void getTileWithID();

private:
	string filename;
	GLuint texture;
	int ID;
	int heightTile, widthTile;
	int numberOfTiles;
};

