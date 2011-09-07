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

	GLuint getTexture() { return texture; }

	std::map< int, std::string > getListCollisionTiles() { return listCollisionTiles; }
	void setListCollisionTiles(std::map< int, std::string > list) { listCollisionTiles = list; }

	int getHeightImage() { return heightImage; }
	void setHeightImage(int height) { heightImage = height; }

	int getWidthImage() { return widthImage; }
	void setWidthImage(int width) { widthImage = width; }

	void setFilename(std::string name) { filename = name; }

	void setHeightTile(int height) { heightTile = height; }

	void setWidthTile(int width) { widthTile = width; }

	void setNumberOfTiles(int number) { numberOfTiles = number; }

	void setTexture(GLuint tex) { texture = tex; }

	void setID(int id) { ID = id; }

private:
	std::string filename;
	GLuint texture;
	int ID;
	int heightTile, widthTile;
	int heightImage, widthImage;
	int numberOfTiles;
	std::map< int, std::string > listCollisionTiles;
};

