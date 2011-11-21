#pragma once

#include "GameText.h"

namespace PlayerScore
{
  class Score
  {
   public:
    Score(void);
    ~Score(void);

	void drawDisplayPoints();

	void initializeTextAndFonts(Font::GameFont* font, std::string text, Vector2f pos, Vector2f off);

	int getPoints() { return points; }
	void addPoints(int value);

   private:
	Text::GameText pointsDisplay;
    int points;
  };
}
