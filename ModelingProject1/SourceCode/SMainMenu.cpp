
#include "SMainMenu.h"

void Image::ArrowMainMenu::updatePositionArrow()
{
  if ( optionSelected == MenuData::NOTHING_SELECTED )
  {
    return;
  } 

  arrow->setPosition(420.0f, 280.0f + ( (optionSelected-1)*50.0f) );
}

SMainMenu::SMainMenu(GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;
  setHasEnded(STATE_MAINMENU);
}

SMainMenu::~SMainMenu(void)
{
}

void SMainMenu::init()
{
  guiMainMenu = new RPRGUI::GUIMenu();

  std::string commonPath = "Resources/Menus/Main Menu/";

  createGUI();

  arrowImage.arrow = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(412.0f, 64.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "MainMenuHighlighter.png");
  arrowImage.optionSelected = MenuData::NOTHING_SELECTED;

  customCursor.cursor = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(64.0f, 64.0f), 
                                             Vector2f(0.0f, 0.0f), "Resources/GUI/Cursor.png");  

  gameCore->getGameTimer()->setFramesPerSecond(30);
}

void SMainMenu::handleEvents()
{
  SDL_Event e;
  bool running = gameCore->getIsRunning();

  while ( SDL_PollEvent(&e) && checkIfStateEnd() == getNameState() )
  {
	Vector2f mousePosition = Vector2f(static_cast<float>(e.motion.x), static_cast<float>(e.motion.y) );

    switch( e.type )
    {
      case SDL_MOUSEBUTTONDOWN:
      {
        handleMouseDown(e.button.button, mousePosition );
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        handleMouseUp(e.button.button, mousePosition);
		setHasEnded( guiMainMenu->getListButtons().at( arrowImage.optionSelected - 1 ).eventClicked(&running) );
		gameCore->setIsRunning(running);
        break;
      }
      case SDL_MOUSEMOTION:
      {
        customCursor.cursor->setPosition(mousePosition.x, mousePosition.y);
		arrowImage.optionSelected = guiMainMenu->checkMousePosition(mousePosition);
        break;
      }
      case SDL_KEYDOWN:
      {
        handleKeyDown(e.key.keysym.sym);
        break;
      }
      case SDL_QUIT:
      {
        running = false;
        break;
      }
    }
  }
}

void SMainMenu::logic()
{
  arrowImage.updatePositionArrow();
}

void SMainMenu::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (std::string::size_type i = 0; i < guiMainMenu->getListStaticImages().size(); i++)
  {
    gameRender->drawFullTexture(guiMainMenu->getTexturesStaticImages().at(i), 
		                        guiMainMenu->getListStaticImages().at(i).getPosition(),
                                guiMainMenu->getListStaticImages().at(i).getOffset().x, 
								guiMainMenu->getListStaticImages().at(i).getOffset().y);
  }

  for (std::string::size_type i = 0; i < guiMainMenu->getListButtons().size(); i++)
  {
    gameRender->drawButton(guiMainMenu->getTextureButtons(),
		                   guiMainMenu->getListButtons().at(i).getPosition(),
		                   guiMainMenu->getListButtons().at(i).getDimensions(),
		                   guiMainMenu->getListButtons().at(i).getTexturePosition());
  }

  if ( arrowImage.optionSelected != MenuData::NOTHING_SELECTED )
  {
    gameRender->drawFullTexture(arrowImage.arrow->getTexture(), arrowImage.arrow->getPosition(),
                                arrowImage.arrow->getOffset().x, arrowImage.arrow->getOffset().y);
  }

  gameRender->drawFullTexture(customCursor.cursor->getTexture(), customCursor.cursor->getPosition(),
                              customCursor.cursor->getOffset().x, customCursor.cursor->getOffset().y);

  SDL_GL_SwapBuffers();
}

void SMainMenu::cleanUp()
{
  delete arrowImage.arrow;
  delete customCursor.cursor;

  delete guiMainMenu;
}

void SMainMenu::createGUI()
{
  RPRGUI::GUIManager* guiManager = gameRender->getGUIManager();
  std::string commonPath = "Resources/Menus/Main Menu/";

  guiMainMenu->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiMainMenu->addTextureStaticImages(gameRender->loadTexture(commonPath + "MainMenuBackground.png"));

  guiMainMenu->addButton( guiManager->createButton(MenuData::HISTORY_MODE, Vector2f(522.0f, 300.0f), 
	                                               Vector2f(230.0f, 28.75f), Vector2f(0.0f, 0.0f),
	                                               STATE_MENUSELECTIONPLAYER) );
  guiMainMenu->addButton( guiManager->createButton(MenuData::TUTORIAL, Vector2f(522.0f, 350.0f), 
	                                               Vector2f(230.0f, 28.75f), Vector2f(0.0f, 28.75f),
	                                               STATE_LEVELONEJAPAN) );
  guiMainMenu->addButton( guiManager->createButton(MenuData::CREDITS, Vector2f(522.0f, 400.0f), 
	                                               Vector2f(230.0f, 28.75f), Vector2f(0.0f, 57.5f),
	                                               STATE_LEVELONEJAPAN) );
  guiMainMenu->addButton( guiManager->createButton(MenuData::QUIT, Vector2f(522.0f, 450.0f), 
	                                               Vector2f(230.0f, 28.75f), Vector2f(0.0f, 86.25f),
	                                               STATE_EXIT) );
  guiMainMenu->addTextureButtons( gameRender->loadTexture(commonPath + "MainMenuButtons.png") );                                               
}

void SMainMenu::handleMouseDown(Uint8 button, Vector2f mousePosition)
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

void SMainMenu::handleMouseUp(Uint8 button, Vector2f mousePosition)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
      arrowImage.optionSelected = guiMainMenu->checkMousePosition(mousePosition);
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

void SMainMenu::handleKeyDown(SDLKey key)
{
  if ( key == SDLK_DOWN )
  {
    if ( arrowImage.optionSelected + 1 > MenuData::QUIT )
    {
      arrowImage.optionSelected = 1;
      return;
    }

    arrowImage.optionSelected += 1;
  }

  if ( key == SDLK_UP )
  {
    if ( arrowImage.optionSelected - 1 == MenuData::NOTHING_SELECTED || 
         arrowImage.optionSelected == MenuData::NOTHING_SELECTED )
    {
      arrowImage.optionSelected = MenuData::QUIT;
      return;
    }

    arrowImage.optionSelected -= 1;
  }

  if ( key == SDLK_RETURN )
  {
    handleEnterPressed();
  }

  if ( key == SDLK_ESCAPE )
  {
    arrowImage.optionSelected = MenuData::QUIT;
  }
}

void SMainMenu::handleEnterPressed()
{
  bool running = gameCore->getIsRunning();

  setHasEnded( guiMainMenu->getListButtons().at( arrowImage.optionSelected - 1 ).eventClicked(&running) );

  gameCore->setIsRunning(running);
}

