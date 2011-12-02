#pragma once

#include "Character.h"

#include "PlayerSprite.h"
#include "Stats.h"
#include "Score.h"
#include "GameInputMapper.h"

namespace Characters
{
  class Player : public Character
  {
    public:
     virtual ~Player() { };

     virtual void initializeCharacter(SpriteData::IDSprites id, std::string filename, Vector2f pos, int initialFrame, 
		                              std::vector < int > maxFrame, std::vector < int > returnFrame, GLfloat widthSprite, 
									  GLfloat heightSprite, std::vector < int > framerateAnimations, 
									  std::vector< Vector2f> delayMovement) = 0;
     virtual void noAction() = 0;
     virtual void walk() = 0;
     virtual void run() = 0;
     virtual void jump() = 0;
     virtual void fastAttack() = 0;
     virtual void falling() = 0;
     virtual void draw() = 0;

     void executeAction();
   
     void stop();

     void returnToPreviousState();

     void drawUIStats();
     void drawScore();
      
     static void inputCallback(InputMapping::MappedInput& inputs, Player& player, std::list<InputMapping::Key> keys);

     InputMapping::GameInputMapper* getInputMapper() { return inputMapper; }

     PlayerStats::Stats* getPlayerStats() { return stats; }

     PlayerScore::Score* getScore() { return score; }

    protected:
     InputMapping::GameInputMapper* inputMapper;
     PlayerStats::Stats* stats;
     PlayerScore::Score* score;
  };
}