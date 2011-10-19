
#include "SMainMenu.h"


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
  CEGUI::WindowManager& windowManager = initializeCEGUI( gameCore->getGameScreen()->getScreenReference() ) ;
 
  createGUI( windowManager ) ;

  gameCore->getGameTimer()->setFramesPerSecond(20);
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
        CEGUI::System::getSingleton().injectMousePosition(static_cast<float>(e.motion.x),static_cast<float>(e.motion.y));
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
        CEGUI::System::getSingleton().injectKeyDown(e.key.keysym.scancode);
        if ( (e.key.keysym.unicode & 0xFF80) == 0 )
		{
          CEGUI::System::getSingleton().injectChar(e.key.keysym.unicode & 0x7F);
        }
        break;
      }
      case SDL_KEYUP:
      {
        CEGUI::System::getSingleton().injectKeyUp(e.key.keysym.scancode);
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
}

void SMainMenu::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  CEGUI::System::getSingleton().renderGUI();

  SDL_GL_SwapBuffers();
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
  CEGUI::ScriptModule::setDefaultResourceGroup( "lua_scripts" );
 
  CEGUI::ImagesetManager::getSingleton().create( "MainMenuBackground.imageset");
  CEGUI::ImagesetManager::getSingleton().create( "MainMenuButtons.imageset");

  CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" ) ;
 
  CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" ) ;
 
  return CEGUI::WindowManager::getSingleton() ;
}

void SMainMenu::createGUI( CEGUI::WindowManager& winManager )
{
  CEGUI::DefaultWindow& rootWin = *static_cast<CEGUI::DefaultWindow*>(
	                                 winManager.createWindow( "DefaultWindow", "Root" ) ) ;
 
  CEGUI::Window* mainMenu = winManager.loadWindowLayout("MainMenu.layout");
  rootWin.addChildWindow(mainMenu);

  CEGUI::PushButton* Button1 = (CEGUI::PushButton*)winManager.getWindow("MainMenu/NewGame");
  Button1->subscribeEvent( CEGUI::PushButton::EventClicked, 
	                       CEGUI::Event::Subscriber(&SMainMenu::handleHistoryMode, this) );

  CEGUI::System::getSingleton().setGUISheet( &rootWin ) ;
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

bool SMainMenu::handleHistoryMode(const CEGUI::EventArgs& e)
{
  setHasEnded(STATE_LEVELZEROTUTORIAL);
  return true;
}