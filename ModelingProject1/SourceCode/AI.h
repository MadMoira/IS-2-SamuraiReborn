#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Pathfinding.h"

class AI
{
  public:
   AI(void);
   virtual ~AI(void);

   void searchPath(Characters::Player* player, Characters::Enemy* enemy);

  private: 
   Pathfinding pathfinding;
};

