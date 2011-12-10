
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

void Text::GameText::setDataText(int data)
{
  dataText = parseDataToString(data);
  if ( data < 100 )
  {
	for ( ; dataText.size() < 3; )
	{
	  dataText += "0" + dataText;
	}
  }
}