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

void PlayerScore::Score::initializeTextAndFonts(Font::GameFont* font, std::string text, int idNumberPlayer)
{
  pointsDisplay = Text::GameText( font, text, Vector2f(120.0f*(idNumberPlayer) + 100.0f, 60.0f),
	                                          Vector2f(50.0f, 20.0f) );
  pointsDisplay.setDataText( points );
}

void PlayerScore::Score::addPoints(int value)
{
  points += value;
  pointsDisplay.setDataText( points );
}

