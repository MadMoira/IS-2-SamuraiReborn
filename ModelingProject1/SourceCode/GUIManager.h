#pragma once

#include "Vector.h"

#include "MenuData.h"

#include "PushButton.h"
#include "GameImage.h"

namespace RPRGUI
{
  class GUIManager
  {
    public:
     GUIManager(void);
     ~GUIManager(void);

     PushButton* createButton(MenuData::MainMenuOptions id, Vector2f pos, Vector2f dimensions, Vector2f posTexture, int idChangeState);
     Image::GameImage* createStaticImage(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, std::string filename);
  };
}

