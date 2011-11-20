#pragma once

#include <boost\noncopyable.hpp>

#include "Sprite.h"
#include "Weapon.h"

#include "Vector.h"

namespace Characters
{
  class Character : boost::noncopyable
  {
    public:
	 virtual ~Character() { };

     virtual void initializeCharacter(SpriteData::IDSprites id, std::string filename, std::vector< Vector2f > speed, 
				                      Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				                      std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
				                      std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement) = 0;
     virtual void noAction() = 0;
     virtual void walk() = 0;
     virtual void run() = 0;
     virtual void jump() = 0;
     virtual void falling() = 0;
     virtual void stopping() = 0;
	 virtual void stop() = 0;

	 virtual void returnToPreviousState() = 0;

	 virtual void draw() = 0;

	 virtual void executeAction() = 0;

     void initializeSpriteCollisionBox(float width, float height, GLfloat offsetX, GLfloat offsetY);

     bool isStoppingMovement(std::list<InputMapping::Key> keys);
     bool isReadyToPace();
     bool isReadyToDoubleJump();
     bool isFalling();
     bool isAlive();

     SpriteData::IDSprites getCharacterID() { return characterSprite->getID(); }

     Sprite* getCharacterSprite() { return characterSprite; }

    protected:
     Sprite* characterSprite;
     Weapon* characterWeapon;
  };
}

