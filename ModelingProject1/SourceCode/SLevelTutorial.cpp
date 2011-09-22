
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
	delete tutorialLevel;
}

void SLevelTutorial::init()
{
	std::vector< GLfloat > speedXVectorPanda;
	speedXVectorPanda.push_back( 0.0f );
	speedXVectorPanda.push_back( 10.0f );
	speedXVectorPanda.push_back( 10.0f );
	speedXVectorPanda.push_back( 35.0f );

	std::vector< GLfloat > speedXVectorMeerkat;
	speedXVectorMeerkat.push_back( 0.0f );
	speedXVectorMeerkat.push_back( 10.0f );
	speedXVectorMeerkat.push_back( 10.0f );
	speedXVectorMeerkat.push_back( 40.0f );

	std::vector < int > maxFrameVector;
	maxFrameVector.push_back( 1 );
	maxFrameVector.push_back( 8 );
	maxFrameVector.push_back( 8 );
	maxFrameVector.push_back( 8 );

	std::vector < int > returnFrameVector;
	returnFrameVector.push_back( 0 );
	returnFrameVector.push_back( 1 );
	returnFrameVector.push_back( 1 );
	returnFrameVector.push_back( 1 );

	gameCore->addPlayerToGame( new PandaP1(), PANDA, "Panda - SpriteSheet.png", 
						speedXVectorPanda, 0.0f, 50.0f, 460.0f, 0, maxFrameVector, returnFrameVector,
						STILL, 187.0f, 187.0f);

	gameCore->addPlayerToGame( new MeerkatP2(), MEERKAT, "Meerkat - SpriteSheet.png", 
						speedXVectorMeerkat, 0.0f, 100.0f, 460.0f, 0, maxFrameVector, returnFrameVector,
						STILL, 204.0f, 187.0f);

	tutorialLevel = new Level(LEVELZEROTUTORIAL);
	tutorialLevel->loadTMXTileMapFile("TutorialMapTest.tmx");	

	//tutorialLevel->addLayerToList("BackGround1.png", 1280.f, 720.f, 2.0f, 0.0f, 0.3f, true);

	tutorialLevel->addLayerToList("nubes.png", 1600.f, 720.f, 1.0f, 0.0f, 0.1f, true);
	tutorialLevel->addLayerToList("mountains.png", 1600.f, 720.f, speedXVectorPanda.at(0), 0.0f, 0.5f, false);

	speedXVectorPanda.clear();
	speedXVectorMeerkat.clear();
	maxFrameVector.clear();
	returnFrameVector.clear();
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
	}
}

void SLevelTutorial::logic()
{
	tutorialLevel->checkLayersSpeed( gameCore->getPlayersList().at(0).getPlayerSprite()->getSpeedX() );
	tutorialLevel->scrollBackgroundLayers();

	tutorialLevel->checkTilemapsSpeed( gameCore->getPlayersList().at(0).getPlayerSprite()->getSpeedX() );
	tutorialLevel->scrollTilemap();

	for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
	{
		gameCore->getPlayersList().at(i).executeAction();
	}
}

void SLevelTutorial::render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	tutorialLevel->drawLevelMap();

	for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
	{
		gameCore->getPlayersList().at(i).draw();
	}

	SDL_GL_SwapBuffers();
}
