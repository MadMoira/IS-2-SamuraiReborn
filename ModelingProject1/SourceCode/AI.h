#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Pathfinding.h"

namespace AISystem
{
  class AI
  {
    public:
     AI();
     virtual ~AI();

     void searchPath(Characters::Player* player, Characters::Enemy* enemy);

    private: 
     Pathfinding pathfinding;
  };
}

