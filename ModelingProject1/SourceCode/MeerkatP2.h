#pragma once

#include "Player.h"

namespace Characters
{
  class MeerkatP2 : public Player
  {
    public:
     ~MeerkatP2();

     void initializePlayer(SpriteData::IDSprites id, std::string filename, std::vector< Vector2f > speed, 
                           Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
                           std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
                           std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement);
     void noAction();
     void walk();
     void run();
     void jump();
     void draw();
     void fastAttack();
     void falling();
     void stopping();
  };
}
