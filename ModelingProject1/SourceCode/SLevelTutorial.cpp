
#include "SLevelTutorial.h"

#include "PandaP1.h"
#include "MeerkatP2.h"
#include "JapaneseMonkey.h"
#include "Pathfinding.h"


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
  speedMeerkat.push_back( Vector2f(10.0f, 0.0f) );

  std::vector < int > maxFrameVector;
  maxFrameVector.push_back( 1 );
  maxFrameVector.push_back( 8 );
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
  returnFrameVector.push_back( 1 );

  SDL_Color color;
  color.r = color.g = color.b = 255;
  int sizeFont = 25;
  std::string filenameFont = "orbitron-black.ttf";

  gameCore->addPlayerToGame( new PandaP1(), PANDA, "Meerkat - SpriteSheet.png", 
						speedMeerkat, Vector2f(150.0f, 350.0f), 0, maxFrameVector, returnFrameVector,
						204.0f, 187.0f);

  gameCore->addEnemyToGame( new JapaneseMonkey(), JAPANESEMONKEY, "Panda - SpriteSheet.png", 
						speedMeerkat, Vector2f(150.0f, 350.0f), 0, maxFrameVector, returnFrameVector,
						187.0f, 187.0f);

  gameCore->getPlayersList().at(0).getScore()->initializeTextAndFonts(
		     new Font::GameFont(TTF_OpenFont(filenameFont.c_str(), sizeFont),
		                   color, filenameFont, sizeFont, 0),  "", Vector2f(170.0f, 15.0f), 
								   Vector2f(200.0f, 20.0f) );

  /*gameCore->addPlayerToGame( new PandaP1(), PANDA, "Panda - SpriteSheet.png", 
						speedPanda, 0.0f, Vector2f(50.0f, 400.0f), 0, maxFrameVector, returnFrameVector,
						STILL, 187.0f, 187.0f);*/

  /*gameCore->addPlayerToGame( new MeerkatP2(), MEERKAT, "Meerkat - SpriteSheet.png", 
						speedMeerkat, 0.0f, Vector2f(100.0f, 400.0f), 0, maxFrameVector, returnFrameVector,
						STILL, 204.0f, 187.0f);*/

  tutorialLevel = new Level(LEVELZEROTUTORIAL);
  tutorialLevel->loadTMXTileMapFile("LevelOneTileMap.tmx");

  tutorialLevel->addLayerToList("FirstLevelZoneOneBG.png", 1280.f, 720.f, Vector2f(0.0f, 0.0f), 0.0f, false, false);
  tutorialLevel->addLayerToList("Clouds.png", 2400.f, 720.f, Vector2f(1.0f, 0.0f), 0.1f, true, true);
  tutorialLevel->addLayerToList("Mountains0.png", 2400.f, 720.f, Vector2f(1.0f, 0.0f), 0.2f, true, false);

  speedPanda.clear();
  speedMeerkat.clear();
  maxFrameVector.clear();
  returnFrameVector.clear();
}

void SLevelTutorial::handleEvents()
{
  gameCore->getPlayersList().at(0).getInputMapper()->clearCurrentMappedInput(
		   GameCoreStates::SpriteState(
		                        gameCore->getPlayersList().at(0).getPlayerSprite()->getCurrentState() ) );

  bool isRunning = gameInput->handleWindowEvents();
  gameCore->setIsRunning( isRunning );

  gameInput->handleKeyEvents( gameCore->getPlayersList().at(0).getInputMapper() );
}

void SLevelTutorial::logic()
{
  Pathfinding pathf;
  gameCore->getPlayersList().at(0).getInputMapper()->dispatchInput( gameCore->getPlayersList().at(0) );

  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {	
    gameCore->getPlayersList().at(i).executeAction();
	pathf.goToPlayer(&gameCore->getEnemyList().at(0),&gameCore->getPlayersList().at(0));//this goes on AI
	gameCore->getEnemyList().at(0).getEnemySprite()->getPosX();
    checkGravity(i); 
  }
  if( gameCore->getCamera()->getOnePlayer() )
	{
		gameCore->getCamera()->setCameraSpeed(	gameCore->getPlayersList().at(0).getPlayerSprite()->getSpeedX(),
												gameCore->getPlayersList().at(0).getPlayerSprite()->getPosX()+
												gameCore->getPlayersList().at(0).getPlayerSprite()->getWidthTexture()/2);
	}
	else{
		gameCore->getCamera()->setCameraSpeed(	gameCore->getPlayersList().at(0).getPlayerSprite()->getSpeedX(),
												gameCore->getPlayersList().at(0).getPlayerSprite()->getPosX(),
												gameCore->getPlayersList().at(1).getPlayerSprite()->getPosX());
	}
	if(gameCore->getCamera()->getCameraSpeed()<0){
		gameCore->getCamera()->getCameraSpeed();
	}
  tutorialLevel->checkLayersSpeed( gameCore->getCamera()->getCameraSpeed() );
  tutorialLevel->scrollBackgroundLayers();

  tutorialLevel->checkTilemapsSpeed( gameCore->getCamera()->getCameraSpeed() );
  tutorialLevel->scrollTilemap();

  gameCore->getCamera()->moveCamera(  );

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
	for (std::string::size_type i = 0; i < gameCore->getEnemyList().size(); i++)
    {
      gameCore->getEnemyList().at(i).draw();
    }

  glPopMatrix();

  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {
    gameCore->getPlayersList().at(i).drawUIStats();
	gameCore->getPlayersList().at(i).drawScore();
  }

  SDL_GL_SwapBuffers();
}
