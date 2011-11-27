
#include "GameCore.h"

GameCore::GameCore(void)
{
  configuration = new GameConfiguration();
  saves = new GameSaves();
  screen = new GameScreen();
  timer = new GameTimer();
  sound = new GameSound();
  camera = Camera::getInstance();
  collider = Collider::getInstance();
  isRunning = true;
}

GameCore::~GameCore(void)
{
  delete configuration;
  delete saves;
  delete screen;
  delete timer;
  delete sound;
  delete camera;
  delete collider;
  playersList.clear();
  enemiesList.clear();
  playersInitialized.clear();
}

bool GameCore::initializeGameCore()
{	
  sound->initSound();
    
  if( screen->initializeScreen())
  {
   camera->initCamera();
   return true;
  }

  collider->initializeColliderSprites(&enemiesList, &playersList);
    
  return true;
}

bool GameCore::cleanUpGameCore()
{
  collider->cleanUpResources();
  sound->closeAll();

  TTF_Quit();
  SDL_Quit();

  return true;
}

void GameCore::startTimer()
{
  timer->start();
}

void GameCore::startMusic(std::string filename)
{
  sound->loadSound(filename);	
}

void GameCore::startSoundEffect(std::string filename)
{
  sound->loadChunk(filename);
}

void GameCore::resetCamera(GLfloat level, GLfloat spawningPoint)
{
  camera->resetCamera(level, spawningPoint);
}

void GameCore::addPlayerToGame(Characters::Player *player, SpriteData::IDSprites id, std::string filename, std::vector< Vector2f> speed, 
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
                std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
                std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  playersList.push_back( player );
  playersList.at(id).initializeCharacter(id, filename, speed, 
                                         pos, initialFrame, maxFrame, returnFrame,
                                         widthSprite, heightSprite, framerateAnimations,
                                         delayMovement);
}

void GameCore::addEnemyToGame(Characters::Enemy *enemy, SpriteData::IDSprites id, std::string filename, std::vector< Vector2f> speed,
                Vector2f pos, int initialFrame, std::vector < int > maxFrame, std::vector < int > returnFrame, 
                GLfloat widthSprite, GLfloat heightSprite, std::vector < int > framerateAnimations,
                std::vector< Vector2f> delayMovement)
{
  enemiesList.push_back( enemy );
  enemiesList.back().initializeCharacter(id, filename, speed, 
                                         pos, initialFrame, maxFrame, returnFrame,
                                         widthSprite, heightSprite, framerateAnimations,
                                         delayMovement);
}

void GameCore::initializeSpriteCollisionBoxPlayer(SpriteData::IDSprites id, float width, float height, GLfloat offsetX, GLfloat offsetY)
{
  for (std::string::size_type i = 0; i < playersList.size(); i++)
  {
    if ( playersList.at(i).getCharacterID() == id )
    {
      playersList.at(i).initializeSpriteCollisionBox(width, height, offsetX, offsetY);
    }
  }
}