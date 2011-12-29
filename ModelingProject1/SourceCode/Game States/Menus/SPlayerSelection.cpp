
#include "SPlayerSelection.h"

#include <PandaP1.h>

#include <Xinput.h>

/*void Image::ControllerSelection::updatePositionController()
{
  if ( selectedPlayer == MenuData::NO_SELECTED_PLAYER )
  {
    controller->setPosition(590.0f, 315.0f);
    return;
  }

  controller->setPosition(520.0f + (selectedPlayer-1)*135.0f, 315.0f);
}*/

void Image::ArrowSelectMenu::updatePositionArrow()
{
  if ( optionSelected == MenuData::NOTHING_SELECTED )
  {
    return;
  } 

  arrow->setPosition(430.0f + (optionSelected - 1)*210.0f, 620.0f );
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

  menuSelectionPlayer = new Image::MenuSelectionPlayer(&controllers.at(0));
  menuSelectionPlayer->setNewIdGameState(GameCoreStates::STATE_MENUSELECTIONPLAYER);
  numberOfPlayers = 1;

  gameCore->getGameTimer()->setFramesPerSecond(30);
}

void SPlayerSelection::handleEvents()
{
  SDL_Event e;
  bool running = gameCore->getIsRunning();

  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {	
    controllers.at(i).getInputMapper()->clearCurrentMappedInput();
  }

  numberOfPlayers = gameInput->countActiveControllers(controllers);

  while ( SDL_PollEvent(&e) )
  {
	Vector2f mousePosition = Vector2f(static_cast<float>(e.motion.x), static_cast<float>(e.motion.y) );

    for (std::string::size_type i = 0; i < controllers.size(); i++)
    {	
	  if ( controllers.at(i).getController()->isEnabled() )
	  {
        gameInput->handleKeyEvents( controllers.at(i).getInputMapper(), 
		                            controllers.at(i).getController() );
	  }
    }

    switch( e.type )
    {
      case SDL_MOUSEMOTION:
      {
		customCursor.cursor->setPosition(mousePosition.x, mousePosition.y);
		arrowImage.optionSelected = guiSelectPlayer->checkMousePosition(mousePosition);
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

  for (std::string::size_type i = 1; i < controllers.size(); i++)
  {	
	if ( controllers.at(i).getController()->isEnabled() )
	{
      gameInput->handleKeyEvents( controllers.at(i).getInputMapper(), 
		                          controllers.at(i).getController() );
	}
  }
}

void SPlayerSelection::logic()
{
  checkSelectedPlayers();
  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {
	if ( controllers.at(i).getController()->isEnabled() )
	{
	  menuSelectionPlayer->setController(&controllers.at(i));
	  menuSelectionPlayer->setCurrentSelection(controllers.at(i).getSelectedPlayer());
	  menuSelectionPlayer->setNumberOfPlayers(numberOfPlayers);
	  menuSelectionPlayer->setPlayerOneSelected(isPlayerOneSelected);
	  menuSelectionPlayer->setPlayerTwoSelected(isPlayerTwoSelected);

      controllers.at(i).getInputMapper()->dispatchInput( Characters::PandaP1(),
	                                      *controllers.at(i).getController()->getListKeys(), 
										  *menuSelectionPlayer );
	  controllers.at(i).updatePositionController(i);

	  if ( menuSelectionPlayer->getNewIdGameState() != getNameState() )
	  {
		handleChangeOfState(menuSelectionPlayer->getNewIdGameState());
		setHasEnded( menuSelectionPlayer->getNewIdGameState() );
		return;
	  }
	}
  }

  arrowImage.updatePositionArrow();
}

void SPlayerSelection::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (std::string::size_type i = 0; i < guiSelectPlayer->getListStaticImages().size(); i++)
  {
    gameRender->drawSpriteTexture(guiSelectPlayer->getTexturesStaticImages().at(i), 
		                          guiSelectPlayer->getListStaticImages().at(i).getPosition(),
								  guiSelectPlayer->getListStaticImages().at(i).getState(),
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

  for ( std::string::size_type i = 0; i < controllers.size(); i++)
  {
    gameRender->drawSpriteTexture(controllers.at(i).getTexture(), controllers.at(i).getPosition(), controllers.at(i).getState(),
                                  controllers.at(i).getOffset().x, controllers.at(i).getOffset().y );
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

void SPlayerSelection::cleanUp()
{
  controllers.clear();
  delete guiSelectPlayer;
  delete menuSelectionPlayer;
}

void SPlayerSelection::createGUI( )
{
  RPRGUI::GUIManager* guiManager = gameRender->getGUIManager();
  std::string commonPath = "Resources/Menus/Menu Selection Player/";

  controllers.push_back( new Image::ImageController(Vector2f(590.0f, 315.0f), Vector2f(100.0f, 67.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "NewKeyboard.png", 
									Image::ENABLE, InputMapping::KEYBOARD) );
  controllers.at(0).setController(GameInput::initializeControllerData(getNameState(), InputMapping::KEYBOARD));
  controllers.at(0).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(0).getController(), InputMapping::KEYBOARD));
  controllers.at(0).getController()->setPlayerID(0);

  controllers.push_back( new Image::ImageController(Vector2f(590.0f, 410.0f), Vector2f(100.0f, 67.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "NewGamepad.png", 
									Image::DISABLE, InputMapping::GAMEPAD) );
  controllers.at(1).setController(GameInput::initializeControllerData(getNameState(), InputMapping::GAMEPAD));
  controllers.at(1).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(1).getController(), InputMapping::GAMEPAD));
  controllers.at(1).getController()->setPlayerID(1);

  controllers.push_back( new Image::ImageController(Vector2f(590.0f, 505.0f), Vector2f(100.0f, 67.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "NewGamepad.png", 
									Image::DISABLE, InputMapping::GAMEPAD) );
  controllers.at(2).setController(GameInput::initializeControllerData(getNameState(), InputMapping::GAMEPAD));
  controllers.at(2).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(2).getController(), InputMapping::GAMEPAD));
  controllers.at(2).getController()->setPlayerID(2);

  arrowImage.arrow = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(208.0f, 65.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "Highlighter.png");
  arrowImage.optionSelected = MenuData::NOTHING_SELECTED;

  customCursor.cursor = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(64.0f, 64.0f), 
                                             Vector2f(0.0f, 0.0f), "Resources/GUI/Cursor.png");  
  
  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "MenuCharacterSelectorBackground.png"));

  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(200.0f, 130.0f), 
	                                                             Vector2f(288.0f, 384.0f), 
	                                                             Vector2f(0.0f, 0.0f),
																 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "PandaSelector.png"));

  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(770.0f, 130.0f),
	                                                         Vector2f(288.0f, 384.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "SuricataSelector.png"));

/*  guiSelectPlayer->addButton( guiManager->createButton(MenuData::BEGIN, Vector2f(405.0f, 640.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 0.0f),
	                                               STATE_LEVELONEJAPAN) );
  guiSelectPlayer->addButton( guiManager->createButton(MenuData::BACK, Vector2f(615.0f, 640.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 32.0f),
	                                               STATE_MAINMENU) );*/

  //guiSelectPlayer->addTextureButtons( gameRender->loadTexture(commonPath + "MenuSelectionPlayerButtons.png") );                                               

}

void SPlayerSelection::checkSelectedPlayers()
{
  boost::ptr_vector<Image::ImageController>::iterator iter = controllers.begin();
  isPlayerOneSelected = false;
  isPlayerTwoSelected = false;

  for ( iter; iter != controllers.end(); iter++ )
  {
    if ( iter->getSelectedPlayer() == MenuData::PLAYER_ONE )
	{
	  isPlayerOneSelected = true;
	}
    if ( iter->getSelectedPlayer() == MenuData::PLAYER_TWO )
	{
	  isPlayerTwoSelected = true;
	}
  }
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
}

void SPlayerSelection::handleEnterPressed()
{
  /*bool running = true;

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
  }*/
}

void SPlayerSelection::checkClickedMouse(bool* running)
{
  handleEnterPressed();
}

void SPlayerSelection::checkControlsButtonsSelected(SDLKey key)
{
}

void SPlayerSelection::handleChangeOfState(int idState)
{
  switch(idState)
  {
    case GameCoreStates::STATE_LEVELONEJAPAN:
	{
      for ( std::string::size_type i = 0; i < controllers.size(); i++)
      {
	    if ( controllers.at(i).getSelectedPlayer() != MenuData::NO_SELECTED_PLAYER )
		{
		  Image::PlayersInitialize initialize;
		  initialize.characterID = controllers.at(i).getSelectedPlayer();
		  if ( initialize.characterID == 2 )
		  {
		    initialize.characterID = 1;
		  }
		  initialize.controllerID = controllers.at(i).getController()->getPlayerID();

		  gameCore->pushBackPlayerToInitialize(initialize);
		}
      }
	  break;
	}
  }
}

void SPlayerSelection::inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                                 std::list<InputMapping::Key> keys, Image::MenuSelection& menu)
{
  const int RIGHT = 1;
  const int LEFT = -1;

  bool moveRight = inputs.actions.find(GameCoreStates::RIGHT) != inputs.actions.end();
  bool moveLeft = inputs.actions.find(GameCoreStates::LEFT) != inputs.actions.end();
  bool continueAction = inputs.actions.find(GameCoreStates::CONTINUE) != inputs.actions.end();

  if ( moveRight )
  {
    if ( menu.getCurrentSelection() <= MenuData::NO_SELECTED_PLAYER && !menu.isPlayerTwoSelected() )
    {
	  menu.moveSelection(RIGHT);
	}
	if ( menu.getCurrentSelection() == MenuData::PLAYER_ONE && menu.isPlayerTwoSelected() )
	{
	  menu.moveSelection(RIGHT);
	}
  }

  if ( moveLeft )
  {
	if ( menu.getCurrentSelection() >= MenuData::NO_SELECTED_PLAYER && !menu.isPlayerOneSelected() )
	{
	  menu.moveSelection(LEFT);
	}
	if ( menu.getCurrentSelection() == MenuData::PLAYER_TWO && menu.isPlayerOneSelected() )
	{
	  menu.moveSelection(LEFT);
	}
  }

  if ( continueAction )
  {
	if ( menu.isPlayerOneSelected() || menu.isPlayerTwoSelected() )
	{
      menu.setNewIdGameState(GameCoreStates::STATE_LEVELONEJAPAN);
	}
  }
}