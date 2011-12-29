#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include "PushButton.h"
#include "ImageObject.h"

namespace Image
{
  class MenuSelection
  {
    public:
	 MenuSelection() { };

	 virtual Image::ImageObject& getController() { return ImageObject(); }

	 virtual void moveSelection(int direction) { };

	 int getCurrentPlayers() { return numberOfPlayers; }
	 void setNumberOfPlayers(int number) { numberOfPlayers = number; }

	 bool isPlayerOneSelected() { return playerOneSelected; }
	 void setPlayerOneSelected(bool selected) { playerOneSelected = selected; }

	 bool isPlayerTwoSelected() { return playerTwoSelected; }
	 void setPlayerTwoSelected(bool selected) { playerTwoSelected = selected; }
     
	 int getCurrentSelection() { return currentSelection; }
	 void setCurrentSelection(int selection) { currentSelection = selection; }

	 int getNewIdGameState() { return idNewGameState; }
	 void setNewIdGameState(int id) { idNewGameState = id; }

    protected:
	 boost::ptr_vector<RPRGUI::PushButton> listButtons;
     boost::ptr_vector<Image::ImageObject> listStaticImages;
	 int currentSelection;
     int idNewGameState;
	 int numberOfPlayers;
	 bool playerOneSelected, playerTwoSelected;
  };
}