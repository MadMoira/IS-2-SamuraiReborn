#pragma once

#include <windows.h>
#include <GL/gl.h>

#include "Vector.h"
#include "StringParser.h"

#include "GameFont.h"

namespace Text
{
  class GameText
  {
    public:
     GameText(Font::GameFont* font, std::string text, Vector2f pos, Vector2f off);
     GameText(){};
     ~GameText(void);

     Font::GameFont* getFont() { return font; }

     std::string getDataText() { return dataText; }

     Vector2f getPosition() { return position; }

     Vector2f getOffset() { return offset; }
     void setOffset(Vector2f off) { offset = off; }

     void setDataText(int data);

    private:
     Font::GameFont* font;
     std::string dataText;
     Vector2f position;
     Vector2f offset;
  };
}

