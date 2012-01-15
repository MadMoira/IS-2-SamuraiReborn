
#include "AI.h"

AISystem::AI::AI(void)
{
}

AISystem::AI::~AI(void)
{
}

void AISystem::AI::searchPath(Characters::Player* player, Characters::Enemy* enemy)
{
  pathfinding.goToPlayer(enemy, player);
}


