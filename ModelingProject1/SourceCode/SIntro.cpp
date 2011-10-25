#include "SIntro.h"


SIntro::SIntro(GameRender* gR, GameCore* gC, GameInput* gI, GamePhysics::PhysicsCore* gP, 
	                                                        GameStates stateName) 
	: GameState( gR, gC, gI, gP, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  gamePhysics = gP;
  nameState = stateName;
  setHasEnded(STATE_INTRO);

  framerate = 6000;
}

SIntro::~SIntro(void)
{
}

void SIntro::init()
{
  logoGameImage = new Image::GameImage( Vector2f(0.0f, 0.0f), Vector2f(1280.0f, 720.0f),
		                                Vector2f(0.0f, 0.0f), "logoSamuraiReborn.png");

  gameCore->getGameTimer()->setFramesPerSecond(20);
}

void SIntro::handleEvents()
{
  bool isRunning = gameInput->handleWindowEvents();
  gameCore->setIsRunning( isRunning );

  if( framerate > SDL_GetTicks() ) 
  {
	return;
  }

  setHasEnded(STATE_MAINMENU);
}

void SIntro::logic()
{
}

void SIntro::render()
{
  glClear( GL_COLOR_BUFFER_BIT );
  
  gameRender->drawFullTexture(logoGameImage->getTexture(), logoGameImage->getPosition(),
	                          logoGameImage->getOffset().x, logoGameImage->getOffset().y);

  SDL_GL_SwapBuffers();
}

void SIntro::cleanUp()
{
  delete logoGameImage;
}
