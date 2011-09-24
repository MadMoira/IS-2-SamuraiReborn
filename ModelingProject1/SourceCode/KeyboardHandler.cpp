
#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler(std::string fileName)
{
	loadKeyValues(fileName);
}


KeyboardHandler::~KeyboardHandler(void)
{
	keyValues.clear();
}

void KeyboardHandler::loadKeyValues(std::string fileName){
	std::ifstream inFile;
	inFile.open(fileName);

	int keyValue;

	for(int i=0;i<4;i++){
		inFile>>keyValue;
		setKeyValues( i, keyValue );
	}
	inFile.close();
}

void KeyboardHandler::setKeyValues(int keyEnum, int keyValue)
{
	keyValues.insert ( std::pair< int, int > (keyEnum, keyValue) );
}