#pragma once

#include "GameState.h"

#include "GUIMenu.h"

#include "MenuData.h"
#include "MenuStructs.h"

class SPlayerSelection : public GameState
{
  public:
   SPlayerSelection( GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName );
   ~SPlayerSelection(void);

   void init();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();

   void createGUI();

   void handleMouseDown(Uint8 button, Vector2f mousePosition);
   void handleMouseUp(Uint8 button, Vector2f mousePosition);
   void handleKeyDown(SDLKey key);
   void handleEnterPressed();

  private:
   RPRGUI::GUIMenu* guiSelectPlayer;
   Image::ControllerSelection controllerImageP1;
   Image::ControllerSelection controllerImageP2;
   Image::CustomCursor customCursor;
};

