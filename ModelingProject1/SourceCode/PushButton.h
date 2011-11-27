#pragma once

#include "Vector.h"

#include "MenuData.h"

namespace RPRGUI
{
  class PushButton
  {
    public:
	 PushButton(MenuData::MainMenuOptions, Vector2f pos, Vector2f dim, Vector2f textPos);
	 ~PushButton(void);

	 Vector2f getPosition() { return position; }

	 Vector2f getDimensions() { return dimensions; }

	 Vector2f getTexturePosition() { return texturePosition; }

	 MenuData::MainMenuOptions getID() { return id; }

	 void setIdChangeState(int id) { idChangeState = id; }

	 int eventClicked(bool* isRunning);

    private:
     MenuData::MainMenuOptions id;
	 Vector2f position;
	 Vector2f dimensions;
	 Vector2f texturePosition;
	 int idChangeState;
  };
}

