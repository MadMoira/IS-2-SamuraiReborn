
#include "SLevelTutorial.h"

SLevelTutorial::SLevelTutorial(GameRender *gR, GameCore *gC, GameInput *gI, GameStates stateName) 
	: GameState( gR, gC, gI, stateName )
{
	gameCore = gC;
	gameRender = gR;
	gameInput = gI;
	nameState = stateName;
	movPhysics = new MovementPhys(-2.0f);
}

SLevelTutorial::~SLevelTutorial(void)
{
	delete movPhysics;
	delete tutorialLevel;
}

void SLevelTutorial::init()
{
	std::vector< Vector2f > speedPanda;
	speedPanda.push_back( Vector2f(0.0f, 0.0f) );
	speedPanda.push_back( Vector2f(10.0f, 0.0f) );
	speedPanda.push_back( Vector2f(0.0f, 0.0f) );
	speedPanda.push_back( Vector2f(35.0f, 0.0f) );

	std::vector< Vector2f > speedMeerkat;
	speedMeerkat.push_back( Vector2f(0.0f, 0.0f) );
	speedMeerkat.push_back( Vector2f(10.0f, 0.0f) );
	speedMeerkat.push_back( Vector2f(0.0f, 0.0f) );
	speedMeerkat.push_back( Vector2f(40.0f, 0.0f) );

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
						speedPanda, 0.0f, Vector2f(50.0f, 460.0f), 0, maxFrameVector, returnFrameVector,
						STILL, 187.0f, 187.0f);


	gameCore->addPlayerToGame( new MeerkatP2(), MEERKAT, "Meerkat - SpriteSheet.png", 
						speedMeerkat, 0.0f, Vector2f(100.0f, 460.0f), 0, maxFrameVector, returnFrameVector,
						STILL, 204.0f, 187.0f);

	tutorialLevel = new Level(LEVELZEROTUTORIAL);
	tutorialLevel->loadTMXTileMapFile("TutorialMapTest.tmx");	

	tutorialLevel->addLayerToList("nubes.png", 1600.f, 720.f, Vector2f(1.0f, 0.0f), 0.1f, true);
	tutorialLevel->addLayerToList("mountains.png", 1600.f, 720.f, speedPanda.at(0), 0.5f, false);

	speedPanda.clear();
	speedMeerkat.clear();
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
	for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
	{
		
		gameCore->getPlayersList().at(i).executeAction();
		checkGravity(i);		 
		
	}

	tutorialLevel->checkLayersSpeed( gameCore->getPlayersList().at(0).getPlayerSprite()->getSpeedX() );
	tutorialLevel->scrollBackgroundLayers();

	tutorialLevel->checkTilemapsSpeed( gameCore->getPlayersList().at(0).getPlayerSprite()->getSpeedX() );
	tutorialLevel->scrollTilemap();
}

void SLevelTutorial::checkGravity(int vPosition)
{
	Vector2f position;

	position.x = gameCore->getPlayersList().at(vPosition).getPlayerSprite()->getSpeedX();
	position.y = gameCore->getPlayersList().at(vPosition).getPlayerSprite()->getSpeedY();

	movPhysics->physicManager(&position, PARABOLIC);

	gameCore->getPlayersList().at(vPosition).getPlayerSprite()->setSpeedX(position.x);
	gameCore->getPlayersList().at(vPosition).getPlayerSprite()->setSpeedY(position.y);
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
