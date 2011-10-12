#pragma once

class Tile
{
public:
	Tile(void);
	Tile(int idTileset, int id);
	~Tile(void);

	int getIDTileset() { return IDTileset; }
	void setIDTileset(int id) { IDTileset = id; }

	int getID() { return ID; }
	void setID(int id) { ID = id; }

private:
	int IDTileset;
	int ID;
};

