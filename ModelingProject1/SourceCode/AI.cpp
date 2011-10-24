#include "AI.h"


AI::AI(void)
{
}

void AI::searchPath(Player* player, Enemy* enemy){
	pathfinding.goToPlayer(enemy, player);
}

AI::~AI(void)
{
}
