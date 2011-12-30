#pragma once

#include "GameState.h"

#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

enum MainMenuOptions
{
  NOTHING_SELECTED,
  HISTORY_MODE,
  TUTORIAL,
  CREDITS,
  QUIT,
};

namespace Image
{
  struct ArrowMenu
  {
    Image::GameImage* arrow;
    int optionSelected;

	void updatePositionArrow();
  };
}

struct MenuButton
{
  CEGUI::PushButton* button;
  int id;
};

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
   Image::ArrowMenu arrowImage;
   std::vector< MenuButton > menuItems;
   GameSound* sound;
};

