#include "KeyboardHandler.h"


KeyboardHandler::KeyboardHandler(void)
{
	setKeyValues( KEY_RIGHT, SDLK_RIGHT );
}

KeyboardHandler::~KeyboardHandler(void)
{
	keyValues.clear();
}

void KeyboardHandler::setKeyValues(int keyEnum, int keyValue)
{
	keyValues.insert ( std::pair< int, int > (keyEnum, keyValue) );
}