
#include <fstream>

#include "Level.h"

#include "TmxParser/Tmx.h"


Level::Level(void)
{
}

Level::~Level(void)
{
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

	log << "Loading Tilesets... " << std::endl;

	for (int i = 0; i < map->GetNumTilesets(); i++) 
	{
		log << "Loading Tileset #0" << i << std::endl;

		const Tmx::Tileset *tileset = map->GetTileset(i);

		tilesetList.push_back( new Tileset() );

		log << "Name: " << tileset->GetName().c_str() << std::endl;
		log << "Margin: " << tileset->GetMargin() << std::endl;
		log << "Spacing: " << tileset->GetSpacing() << std::endl;
		log << "Image Width: " << tileset->GetImage()->GetWidth() << std::endl;
		log << "Image Height: " << tileset->GetImage()->GetHeight() << std::endl;
		log << "Image Source: " << tileset->GetImage()->GetSource().c_str() << std::endl;
		log << "Transparent Color (hex): " << tileset->GetImage()->GetTransparentColor().c_str() << std::endl;
		
		tilesetList.at(i).setID(i);
		tilesetList.at(i).setFilename(tileset->GetImage()->GetSource().c_str());
		tilesetList.at(i).setHeightTile(32);	tilesetList.at(i).setWidthTile(32);
		tilesetList.at(i).setNumberOfTiles( tileset->GetTiles().size() );

		if (tileset->GetTiles().size() > 0) 
		{
			std::map< int, std::string > tempListTilesCollision = tilesetList.at(i).getListCollisionTiles();
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
		}
	}

	log << "Loading Layers... " << std::endl;

	for (int i = 0; i < map->GetNumLayers(); i++) 
	{
		log << "Loading Layer #0" << i << " - " << map->GetLayer(i)->GetName().c_str() << std::endl;

		const Tmx::Layer *layer = map->GetLayer(i);
		
		layersList.push_back( new Layer(map->GetLayer(i)->GetName().c_str(), 
							  layer->GetWidth(), layer->GetHeight()) );

		std::vector< std::vector <int> > tempLayerMap = layersList.at(i).getLayerMap();

		for (int x = 0; x < layer->GetWidth(); x++) 
		{
			for (int y = 0; y < layer->GetHeight(); y++) 
			{
				//printf("%03d", layer->GetTileGid(y, x));
				tempLayerMap[y][x] = layer->GetTileGid(y, x);

				const Tmx::Tileset *tileset = map->FindTileset(layer->GetTileGid(y,x));
			}
		}

		layersList.at(i).setLayerMap(tempLayerMap);
	}

	widthLevelInTiles = layersList.at(0).getWidthLevelLayer();
	heightLevelInTiles = layersList.at(0).getHeightLevelLayer();

	log << "Load Of Map Finished... " << std::endl;
	log << "Closing File... " << std::endl;

	log.close();

	delete map;

	return 0;
}
