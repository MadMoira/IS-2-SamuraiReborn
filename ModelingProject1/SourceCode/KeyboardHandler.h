#pragma once

#include <string>
#include <map>
#include <fstream>

#include "Sprite.h"

#include "SDL/SDL.h"

enum Keys
{
	KEY_RIGHT,
	KEY_LEFT,
	KEY_RUN,
	KEY_JUMP
};

class KeyboardHandler
{
public:
	KeyboardHandler(std::string fileName);
	~KeyboardHandler(void);
		
	std::map< int, int > getKeyValues() { return keyValues; }
	void setKeyValues(int keyValue, int keyEnum);

private:
	void loadKeyValues(std::string fileName);
	std::map< int, int > keyValues;
};

