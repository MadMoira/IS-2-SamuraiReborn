#pragma once

#include <string>
#include <map>

#include "Sprite.h"

#include "SDL.h"

enum Keys
{
	KEY_RIGHT,
	KEY_LEFT,
	KEY_RUN
};

class KeyboardHandler
{
public:
	KeyboardHandler(int buttonRight, int buttonLeft, int buttonRun);
	~KeyboardHandler(void);
		
	std::map< int, int > getKeyValues() { return keyValues; }
	void setKeyValues(int keyValue, int keyEnum);

private:
	std::map< int, int > keyValues;
};

