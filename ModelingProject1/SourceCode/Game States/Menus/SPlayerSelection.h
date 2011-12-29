#pragma once

#include "GameState.h"

#include "GUIMenu.h"

#include "MenuData.h"
#include "MenuStructs.h"

#include <MenuSelectionPlayer.h>

#include <ImageController.h>

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

   void checkSelectedPlayers();

   void handleMouseDown(Uint8 button, Vector2f mousePosition);
   void handleMouseUp(Uint8 button, Vector2f mousePosition);
   void handleKeyDown(SDLKey key);
   void handleEnterPressed();

   void checkClickedMouse(bool* running);
   void checkControlsButtonsSelected(SDLKey key);

   void handleChangeOfState(int idState);

   static void inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                         std::list<InputMapping::Key> keys, Image::MenuSelection& menu);

  private:
   RPRGUI::GUIMenu* guiSelectPlayer;
   Image::MenuSelectionPlayer* menuSelectionPlayer;
   boost::ptr_vector<Image::ImageController> controllers;
   Image::ArrowSelectMenu arrowImage;
   Image::CustomCursor customCursor;
   int numberOfPlayers;
   bool isPlayerOneSelected, isPlayerTwoSelected;
};

