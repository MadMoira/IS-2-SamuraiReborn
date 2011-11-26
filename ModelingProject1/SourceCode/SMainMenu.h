#pragma once

#include "GameState.h"

#include "GUIMenu.h"

#include "MenuData.h"
#include "MenuStructs.h"

class SMainMenu : public GameState
{
  public:
   SMainMenu( GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName );
   ~SMainMenu();

   void init();
   void handleEvents();
   void logic();
   void render();
   void cleanUp();

   void createGUI( );

   void handleMouseDown(Uint8 button, Vector2f mousePosition);
   void handleMouseUp(Uint8 button, Vector2f mousePosition);
   void handleKeyDown(SDLKey key);
   void handleEnterPressed();

  private:
   RPRGUI::GUIMenu* guiMainMenu;
   Image::ArrowMainMenu arrowImage;
};

