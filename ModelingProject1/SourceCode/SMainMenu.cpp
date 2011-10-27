
#include "SMainMenu.h"



void Image::ArrowMenu::updatePositionArrow()
{
  if ( optionSelected == NOTHING_SELECTED )
  {
	return;
  } 

  arrow->setPosition(420.0f, 280.0f + ( (optionSelected-1)*55.0f) );
}

SMainMenu::SMainMenu(GameRender* gR, GameCore* gC, GameInput* gI, GamePhysics::PhysicsCore* gP, 
	                                                              GameStates stateName) 
	: GameState( gR, gC, gI, gP, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  gamePhysics = gP;
  nameState = stateName;
  setHasEnded(STATE_MAINMENU);
}

SMainMenu::~SMainMenu(void)
{
}

void SMainMenu::init()
{
  CEGUI::WindowManager& windowManager = initializeCEGUI( gameCore->getGameScreen()->getScreenReference() );
 
  createGUI( windowManager );

  arrowImage.arrow = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(412.0f, 64.0f), 
	                                Vector2f(0.0f, 0.0f), "MenuHighlighter.png");
  arrowImage.optionSelected = NOTHING_SELECTED;

  gameCore->getGameTimer()->setFramesPerSecond(30);
}

void SMainMenu::handleEvents()
{
  SDL_Event e;

  while ( SDL_PollEvent(&e) )
  {
    switch( e.type )
	{
	  case SDL_MOUSEMOTION:
      {
        CEGUI::System::getSingleton().injectMousePosition( static_cast<float>(e.motion.x),
			                                               static_cast<float>(e.motion.y) );
        verifyCurrentlySelectedItem();
		break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
        handleMouseDown (e.button.button);
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        handleMouseUp (e.button.button);
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

void SMainMenu::logic()
{
  arrowImage.updatePositionArrow();
}

void SMainMenu::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  CEGUI::System::getSingleton().renderGUI();

  if ( arrowImage.optionSelected != NOTHING_SELECTED )
  {
    gameRender->drawFullTexture(arrowImage.arrow->getTexture(), arrowImage.arrow->getPosition(),
		                        arrowImage.arrow->getOffset().x, arrowImage.arrow->getOffset().y );
  }

  SDL_GL_SwapBuffers();
}

void SMainMenu::cleanUp()
{
  delete arrowImage.arrow;

  std::vector< MenuButton >::iterator iter = menuItems.begin();
  for ( iter; iter != menuItems.end(); iter++)
  {
    delete iter->button;
  }

  CEGUI::ImagesetManager::getSingleton().destroyAll();
  //CEGUI::SchemeManager::getSingleton().destroyAll();
}

CEGUI::WindowManager& SMainMenu::initializeCEGUI( SDL_Surface& surface )
{
  CEGUI::DefaultResourceProvider* resourceProvider = (CEGUI::DefaultResourceProvider*) 
         (CEGUI::System::getSingleton().getResourceProvider()); 

  resourceProvider->setResourceGroupDirectory( "schemes", "datafiles/schemes/" ); 
  resourceProvider->setResourceGroupDirectory( "imagesets", "datafiles/imagesets/" ); 
  resourceProvider->setResourceGroupDirectory( "fonts", "datafiles/fonts/" ); 
  resourceProvider->setResourceGroupDirectory( "layouts", "datafiles/layouts/" ); 
  resourceProvider->setResourceGroupDirectory( "looknfeels", "datafiles/looknfeels/" ); 
  resourceProvider->setResourceGroupDirectory( "lua_scripts", "datafiles/lua_scripts/" ); 

  CEGUI::Imageset::setDefaultResourceGroup( "imagesets" ); 
  CEGUI::Font::setDefaultResourceGroup( "fonts" ); 
  CEGUI::Scheme::setDefaultResourceGroup( "schemes" ); 
  CEGUI::WidgetLookManager::setDefaultResourceGroup( "looknfeels" ); 
  CEGUI::WindowManager::setDefaultResourceGroup( "layouts" ); 
 
  CEGUI::ImagesetManager::getSingleton().create( "MainMenuBackground.imageset" );
  CEGUI::ImagesetManager::getSingleton().create( "HistoryModeButton.imageset" );
  CEGUI::ImagesetManager::getSingleton().create( "TutorialButton.imageset" );
  CEGUI::ImagesetManager::getSingleton().create( "CreditsButton.imageset" );
  CEGUI::ImagesetManager::getSingleton().create( "QuitButton.imageset" );
  CEGUI::ImagesetManager::getSingleton().create( "MenuCursor.imageset" );

  CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );
 
  CEGUI::System::getSingleton().setDefaultMouseCursor( "Objects", "Cursor" ) ;
 
  return CEGUI::WindowManager::getSingleton();
}

void SMainMenu::createGUI( CEGUI::WindowManager& winManager )
{
  CEGUI::DefaultWindow& rootWin = *static_cast<CEGUI::DefaultWindow*>(
	                                 winManager.createWindow( "DefaultWindow", "Root" ) ) ;
 
  CEGUI::Window* mainMenu = winManager.loadWindowLayout("MainMenu.layout");

  rootWin.addChildWindow(mainMenu);

  CEGUI::System::getSingleton().setGUISheet( &rootWin ) ;

  menuItems.push_back(MenuButton());
  menuItems.at(0).button = (CEGUI::PushButton*)winManager.getWindow("MainMenu/HistoryMode");
  menuItems.at(0).button->subscribeEvent( CEGUI::PushButton::EventClicked, 
	                                      CEGUI::Event::Subscriber(&SMainMenu::handleHistoryMode, 
										  this) );
  menuItems.at(0).id = HISTORY_MODE;


  menuItems.push_back(MenuButton());
  menuItems.at(1).button = (CEGUI::PushButton*)winManager.getWindow("MainMenu/Tutorial");
  menuItems.at(1).id = TUTORIAL;

  menuItems.push_back(MenuButton());
  menuItems.at(2).button = (CEGUI::PushButton*)winManager.getWindow("MainMenu/Credits");
  menuItems.at(2).id = CREDITS;

  menuItems.push_back(MenuButton());
  menuItems.at(3).button = (CEGUI::PushButton*)winManager.getWindow("MainMenu/Quit");
  menuItems.at(3).button->subscribeEvent( CEGUI::PushButton::EventClicked, 
	                                      CEGUI::Event::Subscriber(&SMainMenu::handleQuit, 
										  this) );
  menuItems.at(3).id = QUIT;
}

void SMainMenu::verifyCurrentlySelectedItem()
{
  std::vector< MenuButton >::iterator iter = menuItems.begin();
  for ( iter; iter != menuItems.end(); iter++)
  {
    if ( iter->button->isHovering() )
    {
      arrowImage.optionSelected = iter->id;
      return;
    }
  }

  arrowImage.optionSelected = NOTHING_SELECTED;
}

void SMainMenu::handleMouseDown(Uint8 button)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
	{
      CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
      break;
	}
    case SDL_BUTTON_MIDDLE:
    {
      CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
      break;
    }
    case SDL_BUTTON_RIGHT:
    {
      CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
      break;
    }
    case SDL_BUTTON_WHEELDOWN:
    {
      CEGUI::System::getSingleton().injectMouseWheelChange( -1 );
      break;
    }
    case SDL_BUTTON_WHEELUP:
    {
      CEGUI::System::getSingleton().injectMouseWheelChange( +1 );
      break;
    }
  }
}

void SMainMenu::handleMouseUp(Uint8 button)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
      CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
      break;
    }
    case SDL_BUTTON_MIDDLE:
    {
      CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
      break;
    }
    case SDL_BUTTON_RIGHT:
    {
      CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
      break;
    }
  }
}

void SMainMenu::handleKeyDown(SDLKey key)
{
  if ( key == SDLK_DOWN )
  {
    if ( arrowImage.optionSelected + 1 > QUIT )
    {
      arrowImage.optionSelected = 1;
      return;
    }

    arrowImage.optionSelected += 1;
  }

  if ( key == SDLK_UP )
  {
    if ( arrowImage.optionSelected - 1 == NOTHING_SELECTED || 
		 arrowImage.optionSelected == NOTHING_SELECTED )
    {
      arrowImage.optionSelected = QUIT;
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
    arrowImage.optionSelected = QUIT;
  }
}

void SMainMenu::handleEnterPressed()
{
  CEGUI::EventArgs e;
  switch( arrowImage.optionSelected )
  {
    case HISTORY_MODE:
    {
      handleHistoryMode(e);
      break;
    }
    case QUIT:
    {
      handleQuit(e);
      break;
    }
  }
}

bool SMainMenu::handleHistoryMode(const CEGUI::EventArgs& e)
{
  setHasEnded(STATE_LEVELONEJAPAN);
  return true;
}

bool SMainMenu::handleQuit(const CEGUI::EventArgs& e)
{
  setHasEnded(STATE_EXIT);
  gameCore->setIsRunning(false);
  return true;
}
