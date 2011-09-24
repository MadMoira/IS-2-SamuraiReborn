
#include "SLevelTutorial.h"

SLevelTutorial::SLevelTutorial(GameRender *gR, GameCore *gC, GameInput *gI, GameStates stateName) 
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

void SLevelTutorial::init()
{
	std::vector < int > maxFrameVector;
	maxFrameVector.push_back( 1 );
	maxFrameVector.push_back( 8 );

	std::vector < int > returnFrameVector;
	returnFrameVector.push_back( 0 );
	returnFrameVector.push_back( 1 );

	gameCore->addPlayerToGame( new PandaP1(), PANDA, "Panda - SpriteSheet1.png", 
						10.0f, 0.0f, 50.0f, 200.0f, 0, maxFrameVector, returnFrameVector,
						STILL, 250.0f, 187.0f);

	gameCore->addPlayerToGame( new MeerkatP2(), MEERKAT, "Meerkat - SpriteSheet.png", 
						12.0f, 0.0f, 50.0f, 200.0f, 0, maxFrameVector, returnFrameVector,
						STILL, 250.0f, 187.0f);
}

void SLevelTutorial::handleEvents()
{
	bool isRunning = gameInput->handleWindowEvents();
	gameCore->setIsRunning( isRunning );

	for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
	{
		bool receivedInput = gameInput->handleKeyStatesPlayers(
										gameCore->getPlayersList().at(i).getKeyboardHandler()->getKeyValues(), 
										gameCore->getPlayersList().at(i).getPlayerSprite(),
										gameCore->getCamera()); 
		if ( receivedInput )
		{
			continue;
		}
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
	//gameCore->getCamera()->render();
	SDL_GL_SwapBuffers();
}
