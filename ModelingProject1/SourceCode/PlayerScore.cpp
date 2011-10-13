#include "PlayerScore.h"
#include "GameRender.h"

Score::PlayerScore::PlayerScore(void)
{
  points = 123456;
}

Score::PlayerScore::~PlayerScore(void)
{
}

void Score::PlayerScore::drawDisplayPoints()
{
  GameRender::drawText(pointsDisplay.getFont(), this->pointsDisplay);
}

void Score::PlayerScore::initializeTextAndFonts(Font::GameFont *font, std::string text, Vector2f pos, Vector2f off)
{
  pointsDisplay = Text::GameText( font, text, pos, off);
  pointsDisplay.setDataText( points );
}

void Score::PlayerScore::addPoints(int value)
{
  points += value;
  pointsDisplay.setDataText( points );
}

