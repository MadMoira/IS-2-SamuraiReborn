#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Pathfinding.h"

class AI
{
public:
	AI(void);

	void searchPath(Player* player, Enemy* enemy);

	virtual ~AI(void);
private: 
	Pathfinding pathfinding;
};

