
#include "SLevelOneJapan.h"

#include "PandaP1.h"
#include "MeerkatP2.h"
#include "JapaneseMonkey.h"

SLevelOneJapan::SLevelOneJapan(GameRender* gR, GameCore* gC, GameInput* gI, GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  gameCore->getGameTimer()->setFramesPerSecond(60);
  setHasEnded(STATE_LEVELONEJAPAN);
}

SLevelOneJapan::~SLevelOneJapan(void)
{
}

void SLevelOneJapan::init()
{
  initializePlayers();
  initializeLevel();

  gameCore->resetCamera(6400.0f, gameCore->getPlayersList().at(0).getCharacterSprite()->getBoxX() +
                                 gameCore->getPlayersList().at(0).getCharacterSprite()->getBoxWidth()/2 );

  Collider::getInstance()->setLevelLength(6400);
}

void SLevelOneJapan::handleEvents()
{
  gameCore->getPlayersList().at(0).getInputMapper()->clearCurrentMappedInput(
           GameCoreStates::SpriteState(
                                gameCore->getPlayersList().at(0).getCharacterSprite()->getCurrentState() ) );

  bool isRunning = gameInput->handleWindowEvents();
  gameCore->setIsRunning( isRunning );

  gameInput->handleKeyEvents( gameCore->getPlayersList().at(0).getInputMapper(), gameCore->getPlayersList().at(0).getController() );
}

void SLevelOneJapan::logic()
{
  gameCore->getPlayersList().at(0).getInputMapper()->dispatchInput( gameCore->getPlayersList().at(0),
	                                                   *gameCore->getPlayersList().at(0).getController()->getListKeys() );
  for (std::string::size_type i = 0; i < gameCore->getPlayersList().size(); i++)
  {	
    gameCore->getPlayersList().at(i).executeAction();
    if ( !gameCore->getPlayersList().at(i).isAlive() )
    {
      setHasEnded(STATE_MENUSELECTIONPLAYER);
    }
  }
  
  //levelAI.searchPath(&gameCore->getPlayersList().at(i),&gameCore->getEnemyList().at(0));
  gameCore->getCamera()->updateCamera(&gameCore->getPlayersList());

  japanLevel->checkLayersSpeed( gameCore->getCamera()->getCameraSpeed() );
  japanLevel->checkTilemapsSpeed( gameCore->getCamera()->getCameraSpeed() );
  japanLevel->scrollContinuousBackgroundLayers();
  
  if ( gameCore->getPlayersList().at(0).getCharacterSprite()->getPlayerMoveInXCurrentFrame() )
  {
    japanLevel->scrollBackgroundLayers();
    japanLevel->scrollTilemap();
  }
  gameCore->getCamera()->setCameraSpeed(0.f);
}

void SLevelOneJapan::render()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	
  
  japanLevel->drawLevelMap();

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

void SLevelOneJapan::cleanUp()
{
  delete japanLevel;
  gameCore->getPlayersList().clear();
  gameCore->getEnemyList().clear();
}

void SLevelOneJapan::initializePlayers()
{
  //gameCore->pushBackPlayerToInitialize(SpriteData::PANDA);
  gameCore->pushBackPlayerToInitialize(SpriteData::MEERKAT);

  std::vector< Vector2f > maxSpeedPanda;
  maxSpeedPanda.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedPanda.push_back( Vector2f(10.0f, 0.0f) );
  maxSpeedPanda.push_back( Vector2f(0.0f, -29.0f) );
  maxSpeedPanda.push_back( Vector2f(18.0f, 0.0f) );
  maxSpeedPanda.push_back( Vector2f(0.0f, -23.0f) );
  maxSpeedPanda.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedPanda.push_back( Vector2f(0.0f, 0.0f)  );
  
  std::vector< Vector2f > maxSpeedMeerkat;
  maxSpeedMeerkat.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedMeerkat.push_back( Vector2f(12.0f, 0.0f) );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, -31.0f) );
  maxSpeedMeerkat.push_back( Vector2f(20.0f, 0.0f) );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, -25.0f) );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, 0.0f)  );
  maxSpeedMeerkat.push_back( Vector2f(0.0f, 0.0f)  );

  std::vector < int > maxFrameVector;
  maxFrameVector.push_back( 0 );
  maxFrameVector.push_back( 8 );
  maxFrameVector.push_back( 5 );
  maxFrameVector.push_back( 6 );
  maxFrameVector.push_back( 6 );
  maxFrameVector.push_back( 4 );
  maxFrameVector.push_back( 2 );
  maxFrameVector.push_back( 6 );

  std::vector < int > maxFrameVectorPanda;
  maxFrameVectorPanda.push_back( 0 );
  maxFrameVectorPanda.push_back( 8 );
  maxFrameVectorPanda.push_back( 5 );
  maxFrameVectorPanda.push_back( 8 );
  maxFrameVectorPanda.push_back( 8 );
  maxFrameVectorPanda.push_back( 5 );
  maxFrameVectorPanda.push_back( 2 );
  maxFrameVectorPanda.push_back( 8 );

  std::vector < int > returnFrameVector;
  returnFrameVector.push_back( 0 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 1 );
  returnFrameVector.push_back( 0 );
  returnFrameVector.push_back( 0 );
  returnFrameVector.push_back( 1 );

  std::vector < Vector2f > delayMovementVector;
  delayMovementVector.push_back( Vector2f(0.0f, 0.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 0.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 4.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 0.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 4.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 4.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 4.0f) );
  delayMovementVector.push_back( Vector2f(2.0f, 0.0f) );

  std::vector < int > framerateAnimationsVector;
  framerateAnimationsVector.push_back( 0 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 70 );
  framerateAnimationsVector.push_back( 100 );
  framerateAnimationsVector.push_back( 100 );

  SDL_Color color;
  color.r = 100;
  color.g = 200;
  color.b = 100;
  int sizeFont = 20;
  std::string filenameFont = "Resources/GUI/Fonts/orbitron-black.ttf";

  for (std::string::size_type i = 0; i < gameCore->getPlayersToInitialize().size(); i++)
  {
    switch(gameCore->getPlayersToInitialize().at(i))
    {
      case SpriteData::PANDA:
      {
        gameCore->addPlayerToGame( new Characters::PandaP1(), SpriteData::PANDA, 
			                 "Resources/Characters/Players/Panda - SpriteSheet.png", 
                             Vector2f(50.0f, 246.0f), 0, maxFrameVectorPanda, returnFrameVector,
                             280.0f, 218.0f, framerateAnimationsVector, delayMovementVector);
        gameCore->initializeSpriteCollisionBoxPlayer(SpriteData::PANDA, 85.0f, 160.0f, 97.0f, 42.0f);
		gameCore->initializeRigidBodyVectors(SpriteData::PANDA, maxSpeedPanda);
		gameCore->setIDNumberOfPlayer(SpriteData::PANDA, (int)i);
		gameCore->getPlayersList().at(i).getScore()->initializeTextAndFonts( new Font::GameFont(TTF_OpenFont(filenameFont.c_str(), sizeFont),
                            color, filenameFont, sizeFont, 0),  "", i);
        break;
      }
      case SpriteData::MEERKAT:
      {
        gameCore->addPlayerToGame( new Characters::MeerkatP2(), SpriteData::MEERKAT, 
			                 "Resources/Characters/Players/Meerkat - SpriteSheet.png", 
                             Vector2f(0.0f, 271.0f), 0, maxFrameVector, returnFrameVector,
                             340.0f, 187.0f, framerateAnimationsVector, delayMovementVector);
        gameCore->initializeSpriteCollisionBoxPlayer(SpriteData::MEERKAT, 32.0f, 135.0f, 153.0f, 42.0f);
		gameCore->initializeRigidBodyVectors(SpriteData::MEERKAT, maxSpeedMeerkat);
		gameCore->setIDNumberOfPlayer(SpriteData::MEERKAT, (int)i);
		gameCore->getPlayersList().at(i).getScore()->initializeTextAndFonts( new Font::GameFont(TTF_OpenFont(filenameFont.c_str(), sizeFont),
                            color, filenameFont, sizeFont, 0),  "", i);
		break;
      }
    }
  }

  maxSpeedPanda.clear();
  maxSpeedMeerkat.clear();
  maxFrameVector.clear();
  returnFrameVector.clear();
  delayMovementVector.clear();
  framerateAnimationsVector.clear();
}

void SLevelOneJapan::initializeLevel()
{
  std::string commonPath = "Resources/Levels/Level One Japan/Section One/";
  japanLevel = new Level(LEVELONEJAPAN);
  japanLevel->loadTMXTileMapFile(commonPath + "LevelOneSectionOneMap.tmx");

  japanLevel->addLayerToList(commonPath + "SkyBackground.png", 1280.f, 720.f, Vector2f(0.0f, 0.0f), 0.0f, false, false);
  japanLevel->addLayerToList(commonPath + "Clouds.png", 2400.f, 720.f, Vector2f(0.1f, 0.0f), 0.1f, true, true);
  japanLevel->addLayerToList(commonPath + "Mountains0.png", 2400.f, 720.f, Vector2f(1.0f, 0.0f), 0.2f, true, false);
  japanLevel->addLayerToList(commonPath + "Mountains1.png", 2400.f, 720.f, Vector2f(1.0f, 0.0f), 0.4f, true, false);
}
