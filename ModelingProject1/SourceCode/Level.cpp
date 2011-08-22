
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

		//tilesetList.push_back( new Tileset() );

		log << "Name: " << tileset->GetName().c_str() << std::endl;
		log << "Margin: " << tileset->GetMargin() << std::endl;
		log << "Spacing: " << tileset->GetSpacing() << std::endl;
		log << "Image Width: " << tileset->GetImage()->GetWidth() << std::endl;
		log << "Image Height: " << tileset->GetImage()->GetHeight() << std::endl;
		log << "Image Source: " << tileset->GetImage()->GetSource().c_str() << std::endl;
		log << "Transparent Color (hex): " << tileset->GetImage()->GetTransparentColor().c_str() << std::endl;
		
		/*tilesetList.at(i)->setFilename(tileset->GetImage()->GetSource().c_str());
		tilesetList.at(i)->setHeightTile(32);	tilesetList.at(i)->setWidthTile(32);
		tilesetList.at(i)->setNumberOfTiles( (tileset->GetImage()->GetWidth()/32) * (tileset->GetImage()->GetHeight()/32) );*/

		if (tileset->GetTiles().size() > 0) 
		{
			const Tmx::Tile *tile = tileset->GetTile(0);

			std::map< std::string, std::string > list = tile->GetProperties().GetList();
			std::map< std::string, std::string >::iterator iter;

			log << "Properties Tiles From This Tileset" << std::endl;

			for (iter = list.begin(); iter != list.end(); iter++) 
			{
				log << iter->first.c_str() << " = " << iter->second.c_str() << std::endl;
			}
		}
	}

	log << "Loading Layers... " << std::endl;

	for (int i = 0; i < map->GetNumLayers(); i++) 
	{
		log << "Loading Layer #0" << i << " - " << map->GetLayer(i)->GetName().c_str() << std::endl;

		const Tmx::Layer *layer = map->GetLayer(i);

		for (int x = 0; x < layer->GetWidth(); x++) 
		{
			for (int y = 0; y < layer->GetHeight(); y++) 
			{
				printf("%03d", layer->GetTileGid(y, x));

				const Tmx::Tileset *tileset = map->FindTileset(layer->GetTileGid(y,x));
			}
		}
	}

	log << "Load Of Map Finished... " << std::endl;
	log << "Closing File... " << std::endl;

	log.close();

	delete map;

	return 0;
}
