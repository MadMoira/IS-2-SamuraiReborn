#include "PathNode.h"

PathNode::PathNode(int ID, int newX, int newY)
{
	this->ID=ID;
	cost=FLT_MAX;
	scoreFunction=FLT_MAX;
	heuristic=FLT_MAX;
	this->x=newX;
	this->y=newY;
}

void PathNode::addAdjacentNode(int ID){
	adjacentID.push_back(ID);
}

PathNode::~PathNode(void)
{
	adjacentID.clear();
}
