#pragma once
#include "Player.h"
#include "Enemy.h"
#include "LevelGraph.h"
#include "HeapCompare.h"
#include "SpriteDataConstants.h"

class Pathfinding
{
public:
	Pathfinding(void);

	void goToPlayer(Characters::Enemy* enemy, Characters::Player* player);
	
	~Pathfinding(void);

	int x, y;

private:
	void goToPosition(Characters::Enemy* enemy);
	bool searchNode(PathNode* node, std::vector<PathNode*> vector);
	void calculatePath(PathNode* node,PathNode* goalNode);
	void setVariablesByPosition(int x, int y, int cost, int heuristic, int score);

	SpriteData::AnimationDirection direction;
	LevelGraph* level;
	std::vector<PathNode*> openNodes;
	std::vector<PathNode*> closedNodes;
	std::vector<PathNode*> path;
};

