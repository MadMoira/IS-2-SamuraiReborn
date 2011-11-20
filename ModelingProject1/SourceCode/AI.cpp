
#include "AI.h"

AI::AI(void)
{
}

AI::~AI(void)
{
}

void AI::searchPath(Characters::Player* player, Characters::Enemy* enemy)
{
  pathfinding.goToPlayer(enemy, player);
}


