
#include "SDL/SDL.h"

#include "GameInput.h"

GameInput::GameInput(void)
{
}

GameInput::~GameInput(void)
{
}

bool GameInput::handleWindowEvents()
{
  SDL_Event evento;

  while( SDL_PollEvent( &evento ) )
  {
    if( evento.type == SDL_KEYDOWN )
    {
      if( evento.key.keysym.sym == SDLK_ESCAPE )
      {  
        return false;
      }   
    }
		
    if( evento.type == SDL_QUIT)
    {
      return false;
    }
  }

  return true;
}

void GameInput::handleKeyEvents(InputMapping::GameInputMapper *gameInputMapper)
{
  gameInputMapper->processNewInput();
}
