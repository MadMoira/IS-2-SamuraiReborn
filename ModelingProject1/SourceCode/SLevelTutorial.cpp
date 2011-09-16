#include "SLevelTutorial.h"

SLevelTutorial::SLevelTutorial(GameRender *gR, GameCore *gC, GameInput *gI, int stateName) 
	: GameState( gR, gC, gI, stateName )
{
	gameCore = gC;
	gameRender = gR;
	gameInput = gI;
	nameState = stateName;
}

SLevelTutorial::~SLevelTutorial(void)
{
}

void SLevelTutorial::handleEvents()
{
	bool isRunning = gameInput->handleWindowEvents();
	gameCore->setIsRunning( isRunning );

	for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
	{
		bool receivedInput = gameInput->handleKeyStatesPlayers(
										gameCore->getPlayersList().at(i).getKeyboardHandler()->getKeyValues(), 
										gameCore->getPlayersList().at(i).getPlayerSprite() ); 
		if ( receivedInput )
		{
			continue;
		}

		gameCore->getPlayersList().at(i).getPlayerSprite()->setCurrentFrame(INITIAL_POSITION);
		gameCore->getPlayersList().at(i).getPlayerSprite()->setCurrentState(STILL);
	}
}

void SLevelTutorial::logic()
{
	for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
	{
		gameCore->getPlayersList().at(i).executeAction();
	}
}

void SLevelTutorial::render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
	{
		gameCore->getPlayersList().at(i).draw();
	}

	SDL_GL_SwapBuffers();
}
