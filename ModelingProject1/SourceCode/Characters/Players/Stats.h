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
    int pointsOfLife, maxPointsOfLife;

    Health(Vector2f lifeQPos, Vector2f lifeQOff, Vector2f lifeIPos, Vector2f lifeIOff);
    Health(){};
  };

  struct FaceState
  {
	Image::GameImage* faces;
	int currentFaceState;
	int maxFaces;
  };

  class Stats
  {
   public:
    Stats(void);
    ~Stats(void);

	void initializeFaceStates(std::string filename, int idPlayer);

	void drawFaceState();
    void drawHealthBar();
    void drawHealth();

    void updatePositionHealthBar(GLfloat positionX);
	void updateFaceState();

   private:
    Health health;
	FaceState faces;
	GLuint textureHealthKills;
  };
}
