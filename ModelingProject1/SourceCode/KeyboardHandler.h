#pragma once

#include <string>
#include <map>

#include "Sprite.h"

#include "SDL/SDL.h"

enum Keys
{
	KEY_RIGHT,
	KEY_LEFT
};

class KeyboardHandler
{
public:
	KeyboardHandler(int buttonRight, int buttonLeft);
	~KeyboardHandler(void);
		
	std::map< int, int > getKeyValues() { return keyValues; }
	void setKeyValues(int keyValue, int keyEnum);

private:
	std::map< int, int > keyValues;
};

