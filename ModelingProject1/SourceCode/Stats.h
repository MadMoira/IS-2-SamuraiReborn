#pragma once

#include <windows.h>
#include <gl\GL.h>

#include "GameImage.h"

namespace PlayerStats
{
  struct Health
  {
    Image::GameImage *healthBar;
	Vector2f lifeQuadPosition, lifeQuadOffset;
	Vector2f lifeInitialPosition, lifeInitialOffset;
	int pointsOfLife;

	Health(Vector2f lifeQPos, Vector2f lifeQOff, Vector2f lifeIPos, Vector2f lifeIOff);
	Health(){};
  };

  class Stats
  {
   public:
	Stats(void);
	~Stats(void);

	void drawHealthBar();
	void drawHealth();

	void updatePositionHealthBar(GLfloat positionX);

   private:
    Health health;
    int stamina;
	int strength, speedAttack;
	int strongStyle, fastStyle;
   };
}
