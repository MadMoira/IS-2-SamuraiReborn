
#include "SPlayerSelection.h"

void Image::ControllerSelection::updatePositionController()
{
  if ( selectedPlayer == MenuData::NO_SELECTED_PLAYER )
  {
    controller->setPosition(590.0f, 330.0f);
    return;
  }

  controller->setPosition(362.5f + (selectedPlayer-1)*420.0f, 430.0f);
}

void Image::ArrowSelectMenu::updatePositionArrow()
{
  if ( optionSelected == MenuData::NOTHING_SELECTED )
  {
    return;
  } 

  arrow->setPosition(300.0f + (optionSelected - 1)*280.0f, 580.0f );
}

SPlayerSelection::SPlayerSelection(GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;
  setHasEnded(STATE_MENUSELECTIONPLAYER);
}

SPlayerSelection::~SPlayerSelection(void)
{
}

void SPlayerSelection::init()
{
  guiSelectPlayer = new RPRGUI::GUIMenu();

  gameCore->clearPlayerToInitialize();

  createGUI();

  gameCore->getGameTimer()->setFramesPerSecond(30);
}

void SPlayerSelection::handleEvents()
{
  SDL_Event e;
  bool running = gameCore->getIsRunning();

  while ( SDL_PollEvent(&e) )
  {
	Vector2f mousePosition = Vector2f(static_cast<float>(e.motion.x), static_cast<float>(e.motion.y) );

    switch( e.type )
    {
      case SDL_MOUSEMOTION:
      {
		customCursor.cursor->setPosition(mousePosition.x, mousePosition.y);
		arrowImage.optionSelected = guiSelectPlayer->checkMousePosition(mousePosition);
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
		handleMouseUp(e.button.button, mousePosition);
		checkClickedMouse(&running);
        break;
      }
      case SDL_KEYDOWN:
      {
		handleKeyDown(e.key.keysym.sym);
        break;
      }
      case SDL_QUIT:
      {
        gameCore->setIsRunning(false);
        break;
      }
    }
  }
}

void SPlayerSelection::logic()
{
  controllerImageP1.updatePositionController();
  arrowImage.updatePositionArrow();
}

void SPlayerSelection::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (std::string::size_type i = 0; i < guiSelectPlayer->getListStaticImages().size(); i++)
  {
    gameRender->drawFullTexture(guiSelectPlayer->getTexturesStaticImages().at(i), 
		                        guiSelectPlayer->getListStaticImages().at(i).getPosition(),
                                guiSelectPlayer->getListStaticImages().at(i).getOffset().x, 
								guiSelectPlayer->getListStaticImages().at(i).getOffset().y);
  }

  for (std::string::size_type i = 0; i < guiSelectPlayer->getListButtons().size(); i++)
  {
	  gameRender->drawButton(guiSelectPlayer->getTextureButtons(),
		                     guiSelectPlayer->getListButtons().at(i).getPosition(),
		                     guiSelectPlayer->getListButtons().at(i).getDimensions(),
		                     guiSelectPlayer->getListButtons().at(i).getTexturePosition());
  }

  gameRender->drawFullTexture(controllerImageP1.controller->getTexture(), controllerImageP1.controller->getPosition(),
                              controllerImageP1.controller->getOffset().x, controllerImageP1.controller->getOffset().y );

  if ( arrowImage.optionSelected != MenuData::NOTHING_SELECTED )
  {
    gameRender->drawFullTexture(arrowImage.arrow->getTexture(), arrowImage.arrow->getPosition(),
                                arrowImage.arrow->getOffset().x, arrowImage.arrow->getOffset().y);
  } 
      

  gameRender->drawFullTexture(customCursor.cursor->getTexture(), customCursor.cursor->getPosition(),
                              customCursor.cursor->getOffset().x, customCursor.cursor->getOffset().y);

  SDL_GL_SwapBuffers();
}

void SPlayerSelection::cleanUp()
{
  delete controllerImageP1.controller;
  //delete controllerImageP2.controller;

  delete guiSelectPlayer;
}

void SPlayerSelection::createGUI( )
{
  RPRGUI::GUIManager* guiManager = gameRender->getGUIManager();
  std::string commonPath = "Resources/Menus/Menu Selection Player/";

  controllerImageP1.controller = new Image::GameImage(Vector2f(590.0f, 330.0f), Vector2f(100.0f, 67.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "Gamepad.png");
  controllerImageP1.selectedPlayer = MenuData::NO_SELECTED_PLAYER;

  arrowImage.arrow = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(412.0f, 64.0f), 
                                    Vector2f(0.0f, 0.0f),"Resources/Menus/Main Menu/MainMenuHighlighter.png");
  arrowImage.optionSelected = MenuData::NOTHING_SELECTED;

  customCursor.cursor = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(64.0f, 64.0f), 
                                             Vector2f(0.0f, 0.0f), "Resources/GUI/Cursor.png");  
  
  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "MenuCharacterSelectorBackground.png"));

  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(300.0f, 100.0f),
	                                                         Vector2f(225.0f, 300.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "PandaSelector.png"));

  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(700.0f, 100.0f),
	                                                         Vector2f(225.0f, 300.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "SuricataSelector.png"));

  guiSelectPlayer->addButton( guiManager->createButton(MenuData::BEGIN, Vector2f(380.0f, 600.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 0.0f),
	                                               STATE_LEVELONEJAPAN) );
  guiSelectPlayer->addButton( guiManager->createButton(MenuData::BACK, Vector2f(650.0f, 600.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 32.0f),
	                                               STATE_MAINMENU) );

  guiSelectPlayer->addTextureButtons( gameRender->loadTexture(commonPath + "MenuSelectionPlayerButtons.png") );                                               

}

void SPlayerSelection::handleMouseDown(Uint8 button, Vector2f mousePosition)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
      break;
    }
    case SDL_BUTTON_MIDDLE:
    {
      break;
    }
    case SDL_BUTTON_RIGHT:
    {
      break;
    }
    case SDL_BUTTON_WHEELDOWN:
    {
      break;
    }
    case SDL_BUTTON_WHEELUP:
    {
      break;
    }
  }
}

void SPlayerSelection::handleMouseUp(Uint8 button, Vector2f mousePosition)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
	  arrowImage.optionSelected = guiSelectPlayer->checkMousePosition(mousePosition);
      break;
    }
    case SDL_BUTTON_MIDDLE:
    {
      break;
    }
    case SDL_BUTTON_RIGHT:
    {
      break;
    }
  }
}

void SPlayerSelection::handleKeyDown(SDLKey key)
{
  checkControlsButtonsSelected(key);

  if ( key == SDLK_UP )
  {
    arrowImage.optionSelected = MenuData::NOTHING_SELECTED;
  }

  if ( key == SDLK_DOWN )
  {
    if ( arrowImage.optionSelected == MenuData::NOTHING_SELECTED )
    {
      arrowImage.optionSelected = MenuData::BEGIN;
    }
  }

  if ( key == SDLK_RETURN )
  {
    handleEnterPressed();
  }
}

void SPlayerSelection::handleEnterPressed()
{
  bool running = true;

  if ( arrowImage.optionSelected != MenuData::NOTHING_SELECTED )
  {
    if ( arrowImage.optionSelected == MenuData::BEGIN && controllerImageP1.selectedPlayer != MenuData::NOTHING_SELECTED )
    {
      gameCore->pushBackPlayerToInitialize(controllerImageP1.selectedPlayer - 1);
	  setHasEnded( guiSelectPlayer->getListButtons().at( arrowImage.optionSelected - 1 ).eventClicked(&running) );
    }

    if ( arrowImage.optionSelected == MenuData::BACK)
    {
      setHasEnded( guiSelectPlayer->getListButtons().at( arrowImage.optionSelected - 1 ).eventClicked(&running) );
    }
  }

  if ( arrowImage.optionSelected == MenuData::NOTHING_SELECTED )
  {
    arrowImage.optionSelected = MenuData::BEGIN;
  }
}

void SPlayerSelection::checkClickedMouse(bool* running)
{
  handleEnterPressed();
}

void SPlayerSelection::checkControlsButtonsSelected(SDLKey key)
{
  if ( key == SDLK_RIGHT )
  {
    switch(arrowImage.optionSelected)
	{
	  case MenuData::BEGIN:
      {
        arrowImage.optionSelected = MenuData::BACK;
        return;
      }
	}

    if ( arrowImage.optionSelected == MenuData::NOTHING_SELECTED )
    {
      switch(controllerImageP1.selectedPlayer)
      {
	    case MenuData::NO_SELECTED_PLAYER:
        {
          controllerImageP1.selectedPlayer = MenuData::PLAYER_TWO;
          break;
		}
	    case MenuData::PLAYER_ONE:
		{
          controllerImageP1.selectedPlayer = MenuData::NO_SELECTED_PLAYER;
          break;
		}
	  }
    }
  }

  if ( key == SDLK_LEFT )
  {
    switch(arrowImage.optionSelected)
	{
	  case MenuData::BACK:
      {
	    arrowImage.optionSelected = MenuData::BEGIN;
        return;
      }
	}

    if ( arrowImage.optionSelected == MenuData::NOTHING_SELECTED )
    {
      switch(controllerImageP1.selectedPlayer)
      {
		case MenuData::NO_SELECTED_PLAYER:
        {
          controllerImageP1.selectedPlayer = MenuData::PLAYER_ONE;
	      break;
        }
		case MenuData::PLAYER_TWO:
        {
          controllerImageP1.selectedPlayer = MenuData::NO_SELECTED_PLAYER;
	      break;
        }
      }
    }
  }
}