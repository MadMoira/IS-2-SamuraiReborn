
#include "SPlayerSelection.h"

void Image::ControllerSelection::updatePositionController()
{
  if ( selectedPlayer == MenuData::NO_SELECTED_PLAYER )
  {
        controller->setPosition(590.0f, 500.0f);
		return;
  }

  controller->setPosition(362.5f + (selectedPlayer-1)*420.0f, 500.0f);
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

  SDL_ShowCursor( 1 );

  createGUI();

  controllerImageP1.controller = new Image::GameImage(Vector2f(590.0f, 500.0f), Vector2f(100.0f, 67.0f), 
                                    Vector2f(0.0f, 0.0f), "Gamepad.png");
  controllerImageP1.selectedPlayer = MenuData::NO_SELECTED_PLAYER;

  gameCore->getGameTimer()->setFramesPerSecond(30);
}

void SPlayerSelection::handleEvents()
{
  SDL_Event e;

  while ( SDL_PollEvent(&e) )
  {
    switch( e.type )
    {
      case SDL_MOUSEMOTION:
      {
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
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
  
  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture("MenuCharacterSelectorBackground.png"));

  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(300.0f, 150.0f),
	                                                         Vector2f(225.0f, 300.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture("PandaSelector.png"));

  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(700.0f, 150.0f),
	                                                         Vector2f(225.0f, 300.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture("SuricataSelector.png"));

  //guiMainMenu->addTextureButtons( gameRender->loadTexture("MainMenuButtons.png") );                                               

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
  if ( key == SDLK_LEFT )
  {
    if ( controllerImageP1.selectedPlayer == MenuData::NO_SELECTED_PLAYER )
    {
      controllerImageP1.selectedPlayer = MenuData::PLAYER_ONE;
    }

    if ( controllerImageP1.selectedPlayer == MenuData::PLAYER_TWO )
    {
      controllerImageP1.selectedPlayer = MenuData::NO_SELECTED_PLAYER;
    }
  }

  if ( key == SDLK_RIGHT )
  {
    if ( controllerImageP1.selectedPlayer == MenuData::NO_SELECTED_PLAYER )
    {
	  controllerImageP1.selectedPlayer = MenuData::PLAYER_TWO;
    }

    if ( controllerImageP1.selectedPlayer == MenuData::PLAYER_ONE )
    {
      controllerImageP1.selectedPlayer = MenuData::NO_SELECTED_PLAYER;
    }
  }
}

void SPlayerSelection::handleEnterPressed()
{
}
