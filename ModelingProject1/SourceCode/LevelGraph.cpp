#include "LevelGraph.h"

LevelGraph::LevelGraph(int levelLength, int levelHeight)
{ 
	mapDivisionX=256;
	mapDivisionY=720;
	this->levelLength=levelLength;
	this->levelHeight=levelHeight;
	idGenerator=0;
	nodes.push_back(Container());										//TODO: check validity of this for multiple rows
	initGraph();
}

void LevelGraph::initGraph(){											//init the graph dividing it by map division x
	int x = mapDivisionX/2,
		y = mapDivisionY/2;
	PathNode newNode(idGenerator, x, y);								//Create the first node and set coordinates
	nodes[0].push_back(newNode);										//push it to vector
	idGenerator++;
	for(int i=1; i<=levelLength/mapDivisionX;i++){						//for the size of the level division					
		std::vector<int> parentNodes;									//create a vector to pass to the add function
		parentNodes.push_back(nodes[0][i-1].getID());					//and push the last inserted node on the first row
		addNode(&parentNodes,											//add node
				nodes[0][i-1].getXCoord()+mapDivisionX,					//with x coordinate	
				nodes[0][i-1].getYCoord());								//and y coordinate
		parentNodes.clear();											//clear the vector for next iteration
	}
}

void LevelGraph::addNode(std::vector<int> *parents, int x, int y){
	PathNode newNode(idGenerator,x,y);									//create the node with the specified id
	idGenerator++;
	for(unsigned i=0;i<parents->size();i++){							//for the size of parents vector
		newNode.addAdjacentNode(parents->at(i));						//add parent to adjacent nodes vector of new node
		nodes[0][parents->at(i)].addAdjacentNode(newNode.getID());		//and add the new node to adjacent of the parent
	}
	nodes[0].push_back(newNode);
}

PathNode* LevelGraph::getNodeByID(int ID){
	int b = ID / mapDivisionY;
	int a = ID % mapDivisionX;
	return &nodes[ID / mapDivisionY][ID % mapDivisionX];
}

LevelGraph::~LevelGraph(void)
{
	nodes.clear();
}
