
#include <fstream>
#include "Level.h"
#include "TmxParser/Tmx.h"

#include "Collider.h"

#include "File.h"

Level::Level(Levels id)
{
  IDLevel = id;
}

Level::~Level(void)
{
  layersList.clear();
  tilemapList.clear();
}

int Level::loadTMXTileMapFile(std::string filename)
{
  std::fstream log ("logLoadMapFile.txt", std::fstream::out);

  Tmx::Map *map = new Tmx::Map();
  map->ParseFile(filename);

  log << "Loading File: " << filename << std::endl;

  if ( map->HasError() ) 
  {
    log << "Error Code: " << map->GetErrorCode() << std::endl;
    log << "Error Text: " << map->GetErrorText().c_str() << std::endl;

    return map->GetErrorCode();
  }

  log << "Loading List Collision Tiles... " << std::endl;
  std::ifstream collisionListFile("CollisionListLevelZeroSectionOne.csv");
	
  unsigned countTiles = readDataTypeFromFile<unsigned>(collisionListFile);
  log << "Number Of Tiles With Collision:  " << countTiles << std::endl;
  std::vector< int > tempCollisionTilesList = getCollisionTilesList();
  for(unsigned i = 0; i < countTiles; i++)
  {
    int tileID = readDataTypeFromFile<int>(collisionListFile);
    tempCollisionTilesList.push_back(tileID);
  }

  collisionListFile.close();
  log << "Finish Loading List Collision Tiles... " << std::endl;
	/*setCollisionTilesList(tempCollisionTilesList);

	Collider::getInstance()->setCollisionTilesList(tempCollisionTilesList);

	tempCollisionTilesList.clear();*/

  log << "Loading Layers... " << std::endl;

  for (int i = 0; i < map->GetNumLayers(); i++) 
  {
    log << "Loading Layer #0" << i << " - " << map->GetLayer(i)->GetName().c_str() << std::endl;

    const Tmx::Layer *layer = map->GetLayer(i);
		
    tilemapList.push_back( new Tilemap(map->GetLayer(i)->GetName().c_str(), 
						   layer->GetWidth(), layer->GetHeight()) );

    std::vector< std::vector < Tile > > tempLayerMap = tilemapList.at(i).getLayerMap();

    int width = layer->GetWidth();
    int height = layer->GetHeight();

    tilemapList.at(i).setWidthLevelInTiles(width);
    tilemapList.at(i).setHeightLevelInTiles(height);

    for (int x = 0; x < width; x++) 
    {
      for (int y = 0; y < height; y++) 
      {
        int tileID = layer->GetTileGid(x, y);
        tempLayerMap[y][x].setID( tileID );
		tempLayerMap[y][x].setHasCollision( initializeCollisionData( tileID, tempCollisionTilesList ) );
      }
    }

	if ( i == 0 ){
		Collider::getInstance()->setLayerMap(tempLayerMap);}

    tilemapList.at(i).setLayerMap(tempLayerMap);
    tempLayerMap.clear();
  }

  log << "Loading Tilesets... " << std::endl;

  for (int i = 0; i < map->GetNumTilesets(); i++) 
  {
    log << "Loading Tileset #0" << i << std::endl;

    const Tmx::Tileset *tileset = map->GetTileset(i);

    log << "Name: " << tileset->GetName().c_str() << std::endl;
    log << "Margin: " << tileset->GetMargin() << std::endl;
    log << "Spacing: " << tileset->GetSpacing() << std::endl;
    log << "Image Width: " << tileset->GetImage()->GetWidth() << std::endl;
    log << "Image Height: " << tileset->GetImage()->GetHeight() << std::endl;
    log << "Image Source: " << tileset->GetImage()->GetSource().c_str() << std::endl;
    log << "Transparent Color (hex): " << tileset->GetImage()->GetTransparentColor().c_str() << std::endl;
		
    for (std::string::size_type j = 0; j < tilemapList.size(); j++)
    {
      tilemapList.at(j).addTileset( j, tileset->GetImage()->GetSource().c_str(),
			                        32.0f, 32.0f, (GLfloat) tileset->GetImage()->GetWidth(), 
									(GLfloat)tileset->GetImage()->GetHeight(), 
			                        tileset->GetTiles().size() );
	}
  }

  log << "Load Of Map Finished... " << std::endl;
  log << "Closing File... " << std::endl;

  log.close();

  delete map;

  return 0;
}

bool Level::initializeCollisionData(int tileID, std::vector< int > listCollisionTiles)
{
  if ( tileID == EMPTY )
  {
    return false;
  }

  for (int i = 0; i < listCollisionTiles.size(); i++)
  {
	if ( listCollisionTiles.at(i) > tileID )
	{
	  return false;
	}

	if ( tileID == listCollisionTiles.at(i) )
	{
	  return true;
	}
  }

  return false;
}

bool Level::drawLevelMap()
{
  for (std::string::size_type i = 0; i < layersList.size(); i++)
  {
    layersList.at(i).drawLayerTexture(1280.f, 720.f);
  }

  for (std::string::size_type j = 0; j < tilemapList.size(); j++)
  {
    tilemapList.at(j).drawTilemap(0);
  }
	
  return true;
}

void Level::addLayerToList(std::string name, GLfloat widthLayer, GLfloat heightLayer, Vector2f vel, 
				 GLfloat constantX, bool hasRepetition, bool continuousScroll)
{
  layersList.push_back( new Layer(name, widthLayer, heightLayer, vel, constantX, hasRepetition,
		                continuousScroll) );
}

void Level::scrollBackgroundLayers()
{
  for (std::string::size_type i = 0; i < layersList.size(); i++)
  {
    layersList.at(i).scrollLayer();
  }
}

void Level::checkLayersSpeed(GLfloat speedX)
{
  for (std::string::size_type i = 1; i < layersList.size(); i++)
  {
    layersList.at(i).setSpeedX(speedX);
  }
}

void Level::scrollTilemap()
{
  for (std::string::size_type i = 0; i < tilemapList.size(); i++)
  {
    tilemapList.at(i).scrollTilemap();
  }
}

void Level::checkTilemapsSpeed(GLfloat speedX)
{
  for (std::string::size_type i = 0; i < tilemapList.size(); i++)
  {
    tilemapList.at(i).setVelocityX(speedX);
  }
}
