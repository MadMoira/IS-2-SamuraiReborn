#pragma once

#include "gamestate.h"

#include <CEGUI.h>

class SMainMenu : public GameState
{
  public:
   SMainMenu( GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName );
   ~SMainMenu();

   void init();
   void handleEvents();
   void logic();
   void render();

   CEGUI::WindowManager& initializeCEGUI( SDL_Surface& surface );
   void createGUI( CEGUI::WindowManager& winManager );

   void handleMouseDown(Uint8 button);
   void handleMouseUp(Uint8 button);

   bool handleHistoryMode( const CEGUI::EventArgs& e );
};

