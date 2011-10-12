
#include "SLevelTutorial.h"

#include "PandaP1.h"
#include "MeerkatP2.h"

SLevelTutorial::SLevelTutorial(GameRender *gR, GameCore *gC, GameInput *gI, GameStates stateName) 
	: GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;
  movPhysics = new MovementPhys(-4.0f);
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
  speedPanda.push_back( Vector2f(0.0f, 0.0f) );

  std::vector< Vector2f > speedMeerkat;
  speedMeerkat.push_back( Vector2f(0.0f, 0.0f) );
  speedMeerkat.push_back( Vector2f(10.0f, 0.0f) );
  speedMeerkat.push_back( Vector2f(0.0f, -22.0f) );
  speedMeerkat.push_back( Vector2f(28.0f, 0.0f) );
  speedMeerkat.push_back( Vector2f(0.0f, -16.0f) );

  std::vector < int > maxFrameVector;
  maxFrameVector.push_back( 1 );
  maxFrameVector.push_back( 8 );
  maxFrameVector.push_back( 8 );
  maxFrameVector.push_back( 8 );
  maxFrameVector.push_back( 8 );

  std::vector < int > returnFrameVector;
  returnFrameVector.push_back( 0 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );

  gameCore->addPlayerToGame( new PandaP1(), PANDA, "Meerkat - SpriteSheet.png", 
						speedMeerkat, Vector2f(50.0f, 400.0f), 0, maxFrameVector, returnFrameVector,
						204.0f, 187.0f);

  /*gameCore->addPlayerToGame( new PandaP1(), PANDA, "Panda - SpriteSheet.png", 
						speedPanda, 0.0f, Vector2f(50.0f, 400.0f), 0, maxFrameVector, returnFrameVector,
						STILL, 187.0f, 187.0f);*/

  /*gameCore->addPlayerToGame( new MeerkatP2(), MEERKAT, "Meerkat - SpriteSheet.png", 
						speedMeerkat, 0.0f, Vector2f(100.0f, 400.0f), 0, maxFrameVector, returnFrameVector,
						STILL, 204.0f, 187.0f);*/

  tutorialLevel = new Level(LEVELZEROTUTORIAL);
	tutorialLevel->loadTMXTileMapFile("LevelOneTileMap.tmx");

  tutorialLevel->addLayerToList("nubes.png", 1600.f, 720.f, Vector2f(1.0f, 0.0f), 0.1f, true);

	gameCore->getPlayersList().at(0).getPlayerSprite()->getPosX();
	
  speedPanda.clear();
  speedMeerkat.clear();
  maxFrameVector.clear();
  returnFrameVector.clear();
}

void SLevelTutorial::handleEvents()
{
  gameCore->getPlayersList().at(0).getInputMapper()->clearCurrentMappedInput(
		GameCoreStates::SpriteState(gameCore->getPlayersList().at(0).getPlayerSprite()->getCurrentState()) );

  bool isRunning = gameInput->handleWindowEvents();
  gameCore->setIsRunning( isRunning );

  gameInput->handleKeyEvents( gameCore->getPlayersList().at(0).getInputMapper() );
}

void SLevelTutorial::logic()
{
  gameCore->getPlayersList().at(0).getInputMapper()->dispatchInput( gameCore->getPlayersList().at(0) );

  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {	
    gameCore->getPlayersList().at(i).executeAction();
		gameCore->getCamera()->setCameraSpeed(gameCore->getPlayersList().at(i).getPlayerSprite()->getSpeedX());
    checkGravity(i); 
  }

	tutorialLevel->checkLayersSpeed( gameCore->getCamera()->getCameraSpeed() );
  tutorialLevel->scrollBackgroundLayers();

	std::cout << gameCore->getCamera()->getCameraSpeed() << std::endl;

	tutorialLevel->checkTilemapsSpeed( gameCore->getCamera()->getCameraSpeed() );
  tutorialLevel->scrollTilemap();

	if(gameCore->getCamera()->getOnePlayer()){
		gameCore->getCamera()->moveCamera(gameCore->getPlayersList().at(0).getPlayerSprite()->getPosX());
	}
	else{
		gameCore->getCamera()->moveCamera(gameCore->getPlayersList().at(0).getPlayerSprite()->getPosX(),
			gameCore->getPlayersList().at(1).getPlayerSprite()->getPosX());
	}

	gameCore->getCamera()->restartCameraSpeed();

}

void SLevelTutorial::checkGravity(int vPosition)
{
  Vector2f speed;

  speed.x = gameCore->getPlayersList().at(vPosition).getPlayerSprite()->getSpeedX();
  speed.y = gameCore->getPlayersList().at(vPosition).getPlayerSprite()->getSpeedY();

  movPhysics->physicManager(&speed, PARABOLIC);

  gameCore->getPlayersList().at(vPosition).getPlayerSprite()->setSpeedX(speed.x);
  gameCore->getPlayersList().at(vPosition).getPlayerSprite()->setSpeedY(speed.y);
}

void SLevelTutorial::render()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	

  tutorialLevel->drawLevelMap();

	glPushMatrix();
	gameCore->getCamera()->renderCamera();
  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {
    gameCore->getPlayersList().at(i).draw();
  }
	glPopMatrix();
  SDL_GL_SwapBuffers();
}
