#pragma once
#include "PathNode.h"
#include <vector>

typedef std::vector<PathNode> Container;
class LevelGraph
{
public:
	LevelGraph(int levelLength, int levelHeight);

	void initGraph();
	PathNode* getNodeByPosition(int xPosition, int yPosition){return &nodes[yPosition/mapDivisionY][xPosition/mapDivisionX];}
	PathNode* getNodeByID(int ID);
	int getNodeXIndex(PathNode node);
	void addNode(std::vector<int> *parentNodes, int x, int y);

	~LevelGraph(void);
private:
	std::vector<Container> nodes;
	int mapDivisionX;   //Number of pixels per Node in the map (horizontal).
	int mapDivisionY;	//Number of pixels per Node in the map (vertical).
	int levelLength;
	int levelHeight;
	int idGenerator;
};