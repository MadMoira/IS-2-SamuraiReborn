#pragma once

#include "GameState.h"

#include "MenuData.h"
#include "MenuStructs.h"

#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

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

   CEGUI::WindowManager& initializeCEGUI( SDL_Surface& surface );
   void createGUI( CEGUI::WindowManager& winManager );

   void verifyCurrentlySelectedItem();

   void handleMouseDown(Uint8 button);
   void handleMouseUp(Uint8 button);
   void handleKeyDown(SDLKey key);
   void handleEnterPressed();

   bool handleHistoryMode( const CEGUI::EventArgs& e );
   bool handleQuit( const CEGUI::EventArgs& e );

  private:
   Image::ArrowMainMenu arrowImage;
   std::vector< MenuStructs::MenuButton > menuItems;
};

