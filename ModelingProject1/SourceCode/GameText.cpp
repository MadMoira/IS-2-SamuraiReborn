
#include "GameText.h"

Text::GameText::GameText(Font::GameFont* font, std::string text, Vector2f pos, Vector2f off)
{
  this->font = font;
  dataText = text;
  position = pos;
  offset = off;
}

Text::GameText::~GameText(void)
{
}
