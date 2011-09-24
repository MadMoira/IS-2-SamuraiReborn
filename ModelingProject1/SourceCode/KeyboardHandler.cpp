
#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler(int buttonRight, int buttonLeft)
{
	setKeyValues( KEY_RIGHT, buttonRight );
	setKeyValues( KEY_LEFT, buttonLeft );
}

KeyboardHandler::~KeyboardHandler(void)
{
	keyValues.clear();
}

void KeyboardHandler::setKeyValues(int keyEnum, int keyValue)
{
	keyValues.insert ( std::pair< int, int > (keyEnum, keyValue) );
}