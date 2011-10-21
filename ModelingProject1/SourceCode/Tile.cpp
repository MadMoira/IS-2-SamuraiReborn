#include "Tile.h"


Tile::Tile(void)
{
  IDTileset = ID = 0;
}
Tile::Tile(int idTileset, int id)
{
  IDTileset = idTileset;
  ID = id;
}

Tile::~Tile(void)
{
}
