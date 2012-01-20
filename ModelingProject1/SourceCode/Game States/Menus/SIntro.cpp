#include "SIntro.h"


SIntro::SIntro(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(30);

  setHasEnded(MainStates::STATE_INTRO);
  setProperty(MainStates::NORMAL_MENU);

  currentLogo = 0;

  framerate = 6000;
}

SIntro::~SIntro(void)
{
}

void SIntro::init()
{
  std::string commonPath = "Resources/Menus/Intro/";
  logos.push_back( new Image::GameImage( Vector2f(0.0f, 0.0f), 
	                                    Vector2f(1280.0f, 720.0f),
                                        Vector2f(0.0f, 0.0f), 
										commonPath + "LogoSamuraiReborn.png" ) );
  logos.push_back( new Image::GameImage( Vector2f(0.0f, 0.0f), 
	                                     Vector2f(696.0f, 285.0f),
                                         Vector2f(0.0f, 0.0f), 
								         commonPath + "LogoBrainstormInteractive.png" ) );
}

void SIntro::handleEvents()
{
  bool isRunning = gameInput->handleWindowEvents();
  gameCore->setIsRunning( isRunning );

  if( framerate > SDL_GetTicks() ) 
  {
	currentLogo += 1;
    return;
  }

  setHasEnded(MainStates::STATE_MAINMENU);
}

void SIntro::logic()
{
  if ( currentLogo == 1 )
  {
	
  }
}

void SIntro::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  gameRender->drawFullTexture(logos.at(currentLogo).getTexture(), logos.at(currentLogo).getPosition(),
                              logos.at(currentLogo).getOffset().x, logos.at(currentLogo).getOffset().y);

  SDL_GL_SwapBuffers();
}

void SIntro::cleanUp()
{
  logos.clear();
}
