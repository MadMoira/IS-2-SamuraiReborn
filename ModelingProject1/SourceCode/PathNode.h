#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <vector>

class PathNode
{
public:
	PathNode(int ID, int x, int y);	

	void setID(unsigned nuevoID){ID=nuevoID;}
	int getID(){return ID;}
	void addAdjacentNode(int ID);
	std::vector<int>* getAdjacentNodes(){return &adjacentID;}
	void setCoordinates(int newX, int newY){this->x=newX; this->y=newY;}
	int getXCoord(){return x;}
	int getYCoord(){return y;}

	~PathNode(void);

	GLfloat cost;
	GLfloat heuristic;
	GLfloat scoreFunction;
private:
	int x,y;
	int ID;
	std::vector<int> adjacentID;
};


