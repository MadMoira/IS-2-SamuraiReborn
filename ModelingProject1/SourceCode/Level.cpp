
#include <fstream>

#include "Level.h"

#include "TmxParser/Tmx.h"

Level::Level(void)
{
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

	if (map->HasError()) 
	{
		log << "Error Code: " << map->GetErrorCode() << std::endl;
		log << "Error Text: " << map->GetErrorText().c_str() << std::endl;

		return map->GetErrorCode();
	}

	log << "Loading Layers... " << std::endl;

	for (int i = 0; i < map->GetNumLayers(); i++) 
	{
		log << "Loading Layer #0" << i << " - " << map->GetLayer(i)->GetName().c_str() << std::endl;

		const Tmx::Layer *layer = map->GetLayer(i);
		
		tilemapList.push_back( new Tilemap(map->GetLayer(i)->GetName().c_str(), 
							  layer->GetWidth(), layer->GetHeight()) );

		std::vector< std::vector <int> > tempLayerMap = tilemapList.at(i).getLayerMap();
		int width = layer->GetWidth();
		int height = layer->GetHeight();

		tilemapList.at(i).setWidthLevelInTiles(width);
		tilemapList.at(i).setHeightLevelInTiles(height);

		for (int x = 0; x < width; x++) 
		{
			for (int y = 0; y < height; y++) 
			{
				int tileID = layer->GetTileGid(x, y);
				
				if (tileID == 0){
					tempLayerMap[y][x] = 0;
				}
				
				else{
					tempLayerMap[y][x] = tileID;}
			}
		}

		tilemapList.at(i).setLayerMap(tempLayerMap);
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
		
		tilemapList.at(i).addTileset( i, tileset->GetImage()->GetSource().c_str(),
			32.0f, 32.0f, (GLfloat) tileset->GetImage()->GetWidth(), (GLfloat)tileset->GetImage()->GetHeight(), 
			tileset->GetTiles().size() );
	
		if (tileset->GetTiles().size() > 0) 
		{
			std::map< int, std::string > tempListTilesCollision = tilemapList.at(i).getTilesetList().at(i).getListCollisionTiles();
			std::pair< std::map< int, std::string >::iterator, bool > ret;

			const Tmx::Tile *tile = tileset->GetTile(0);

			std::map< std::string, std::string > list = tile->GetProperties().GetList();
			std::map< std::string, std::string >::iterator iter;

			log << "Properties Tiles From This Tileset" << std::endl;

			for (iter = list.begin(); iter != list.end(); iter++) 
			{
				int tileNumber = 0;

				try
				{      
					tileNumber = boost::lexical_cast< int >( iter->first.c_str() );

				}catch( const boost::bad_lexical_cast & ){   
					log << "Error Processing Property Of Tile: " << iter->first.c_str() << std::endl;
				}

				tempListTilesCollision.insert( std::pair<int,std::string>(tileNumber,iter->second.c_str()) );

				log << iter->first.c_str() << " = " << iter->second.c_str() << std::endl;
			}

			tilemapList.at(i).getTilesetList().at(i).setListCollisionTiles(tempListTilesCollision);
		}
	}

	log << "Load Of Map Finished... " << std::endl;
	log << "Closing File... " << std::endl;

	log.close();

	delete map;

	return 0;
}

bool Level::drawLevelMap()
{
	for (std::string::size_type i = 0; i < layersList.size(); i++)
	{
		layersList.at(i).drawLayerTexture(1280.f, 720.f);
	}

	GLfloat sizeTile = 32.0f;

	for (std::string::size_type i = 0; i < tilemapList.size(); i++)
	{
		tilemapList.at(i).drawTilemap(32.0f, i);
	}
	
	return true;
}

void Level::addLayerToList(std::string name, GLfloat widthLayer, GLfloat heightLayer, GLfloat velX, GLfloat velY)
{
	layersList.push_back( new Layer(name, widthLayer, heightLayer, velX, velY) );
}

void Level::scrollBackgroundLayers()
{
	for (std::string::size_type i = 0; i < layersList.size(); i++)
	{
		layersList.at(i).scrollLayer();
	}
}
