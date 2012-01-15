#pragma once

#include "Character.h"

#include "EnemySprite.h"

namespace Characters
{
  class Enemy : public Character
  {
    public:

     virtual void initializeCharacter(SpriteData::IDSprites id, std::string filename, Vector2f pos, int initialFrame, 
		                              std::vector < int > maxFrame, std::vector < int > returnFrame, GLfloat widthSprite, 
									  GLfloat heightSprite, std::vector < int > framerateAnimations,
                                      std::vector< Vector2f> delayMovement) = 0;
     virtual void noAction() = 0;
     virtual void walk() = 0;
     virtual void run() = 0;
     virtual void jump() = 0;
     virtual void attack() = 0;
     virtual void falling() = 0;
     virtual void draw() = 0;

     void executeAction();
   
     void stop();

     void returnToPreviousState();

    protected:
     int health;
     int modeIA;
     int pointsForDeath;
  };
}
