#pragma once

#include <string>
#include <map>

#include "SDL/SDL.h"

enum Keys
{
	KEY_RIGHT
};

class KeyboardHandler
{
public:
	KeyboardHandler(void);
	~KeyboardHandler(void);
		
	std::map< int, int > getKeyValues() { return keyValues; }
	void setKeyValues(int keyValue, int keyEnum);

private:
	std::map< int, int > keyValues;
};

