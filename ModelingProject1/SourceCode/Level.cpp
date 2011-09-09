
#include <fstream>

#include "Level.h"

#include "TmxParser/Tmx.h"


Level::Level(void)
{
}

Level::~Level(void)
{
	layersList.clear();
	tilesetList.clear();
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
		tilesetList.at(i).setHeightImage( tileset->GetImage()->GetHeight() );		
		tilesetList.at(i).setWidthImage( tileset->GetImage()->GetWidth() );
		tilesetList.at(i).setNumberOfTiles( tileset->GetTiles().size() );

		tilesetList.at(i).setTexture(GameCore::loadTexture("grass.png"));

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

			tilesetList.at(i).setListCollisionTiles(tempListTilesCollision);
		}
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

	log << "Load Of Map Finished... " << std::endl;
	log << "Closing File... " << std::endl;

	log.close();

	delete map;

	return 0;
}

bool Level::drawLevelMap()
{
	for (int i = 0; i < layersList.size(); i++)
	{
		layersList.at(i).drawLayerTexture(1280.f, 720.f);
	}

	GLfloat sizeTile = 32.0f;

	for (int i = 0; i < tilemapList.size(); i++)
	{
		std::vector< std::vector <int> > layerMap = tilemapList.at(0).getLayerMap();
		int widthTilesetImage = tilesetList.at(i).getWidthImage();
		int heightTilesetImage = tilesetList.at(i).getHeightImage();

		int widthMap = tilemapList.at(i).getWidthLevelInTiles();
		int heigthMap = tilemapList.at(i).getHeightLevelInTiles();

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );	
	
		glBindTexture( GL_TEXTURE_2D, tilesetList.at(i).getTexture() );
	
		for (int i = 0; i < heigthMap; i++)
		{
			for (int j = 0; j < widthMap; j++)
			{
				int frameIndex = layerMap[i][j];

				if (frameIndex == 0)
				{ 
					continue; 
				}

				frameIndex -= 1;
			
				const GLfloat tileX = 0.0f + (sizeTile*j);
				const GLfloat tileY = 0.0f + (sizeTile*i);

				const GLfloat verts[] = {
					tileX, tileY,
					tileX + sizeTile, tileY,
					tileX + sizeTile, tileY + sizeTile,
					tileX, tileY + sizeTile
				};

				const GLfloat textureWidth = sizeTile / (GLfloat)widthTilesetImage;
				const GLfloat textureHeight = sizeTile / (GLfloat)heightTilesetImage;
				const int numFramePerRow = (GLfloat)widthTilesetImage / sizeTile;
				const GLfloat textureX = (frameIndex % numFramePerRow) * textureWidth;
				const GLfloat textureY = (frameIndex / numFramePerRow ) * textureHeight;

				const GLfloat texVerts[] = {
						textureX, textureY,
						textureX + textureWidth, textureY,
						textureX + textureWidth, textureY + textureHeight,
						textureX, textureY + textureHeight
				};
			
				glVertexPointer(2, GL_FLOAT, 0, verts);
				glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
				glDrawArrays(GL_QUADS, 0, 4);

			}
		}		
	
		glDisableClientState( GL_VERTEX_ARRAY );			
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );	
	}

	return true;
}

void Level::addLayerToList(std::string name, GLfloat widthLayer, GLfloat heightLayer, GLfloat velX, GLfloat velY)
{
	layersList.push_back( new Layer(name, widthLayer, heightLayer, velX, velY) );
}

void Level::scrollBackgroundLayers()
{
	for (int i = 0; i < layersList.size(); i++)
	{
		layersList.at(i).scrollLayer();
	}
}
