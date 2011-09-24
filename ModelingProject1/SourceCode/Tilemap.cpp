
#include "Tilemap.h"

Tilemap::Tilemap(std::string name, int widthInTiles, int heightInTiles)
{
	nameLayer = name;
	widthLevelInTiles = widthInTiles;
	heightLevelInTiles = heightInTiles;
	offsetX = offsetY = 0.0f;

	layerMap.resize(heightLevelInTiles);
	
	for (int i = 0; i < heightLevelInTiles; i++)
	{
		layerMap[i].resize(widthLevelInTiles);
	}
}

Tilemap::~Tilemap(void)
{
	layerMap.clear();
}

bool Tilemap::drawTilemap(GLfloat sizeTile, int indexTileset)
{
	offsetX++;
	if (offsetX >= 320.f) offsetX = 320.f;

	GLfloat widthTilesetImage = tilesetList.at(indexTileset).getWidthImage();
	GLfloat heightTilesetImage = tilesetList.at(indexTileset).getHeightImage();

	int widthMap = 40 + (int)offsetX/32;
	int heigthMap = 23;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );	
	
	glBindTexture( GL_TEXTURE_2D, tilesetList.at(indexTileset).getTexture() );

	for (int i = 0; i < heigthMap; i++)
	{
		int startX = (int)offsetX/32;

		for (int j = 0; j < 40; j++) 
		{
			int frameIndex = layerMap[i][startX];
			
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
			const int numFramePerRow = (int)widthTilesetImage / (int)sizeTile;
			const GLfloat textureX = ((frameIndex % numFramePerRow) * textureWidth);
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

			startX++;
		}	
	}

	glDisableClientState( GL_VERTEX_ARRAY );			
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );

	return true;
}

void Tilemap::addTileset(int id, std::string name, GLfloat widthTile, GLfloat heightTile, GLfloat imageWidth, GLfloat imageHeight, 
			int size)
{
	tilesetList.push_back( new Tileset(id, name, widthTile, heightTile, imageWidth, imageHeight, size, GameRender::loadTexture(name)) );
}