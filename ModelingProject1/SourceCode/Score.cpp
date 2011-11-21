#include "Score.h"
#include "GameRender.h"

PlayerScore::Score::Score(void)
{
  points = 0000000;
}

PlayerScore::Score::~Score(void)
{
}

void PlayerScore::Score::drawDisplayPoints()
{
  GameRender::drawText(pointsDisplay.getFont(), this->pointsDisplay);
}

void PlayerScore::Score::initializeTextAndFonts(Font::GameFont* font, std::string text, Vector2f pos, Vector2f off)
{
  pointsDisplay = Text::GameText( font, text, pos, off);
  pointsDisplay.setDataText( points );
}

void PlayerScore::Score::addPoints(int value)
{
  points += value;
  pointsDisplay.setDataText( points );
}

