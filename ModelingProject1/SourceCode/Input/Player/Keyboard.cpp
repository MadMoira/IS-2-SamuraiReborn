
#include "Keyboard.h"

#include <SpriteDataConstants.h>
#include <algorithm>

InputMapping::Keyboard::Keyboard(int id) : Controller (id)
{
}

void InputMapping::Keyboard::parseRawInput(InputMapping::Key& key, InputMapping::MappedInput& inputs)
{
  switch(key.button)
  {
    case SDLK_LSHIFT:
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_LSHIFT; 
      break;
    }
    case SDLK_RIGHT:  
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_RIGHT;

      if ( key.isPressed )
      {
        inputs.directionKeyPressed = SpriteData::RIGHT; 
      }
      
      break;
    }
    case SDLK_LEFT:  
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_LEFT;

      if ( key.isPressed )
      {
        inputs.directionKeyPressed = SpriteData::LEFT; 
      }

      break;
    }
    case SDLK_z:
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_Z; 
      break;
    }

    case SDLK_x:
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_X; 
      break;
    }
  } 
}

bool isWalkingRightPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_RIGHT;
}

bool isWalkingLeftPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_LEFT;
}

InputMapping::Key InputMapping::Keyboard::getKeyDirectionX(int directionX)
{
  std::list<InputMapping::Key>::iterator iter;
  if ( directionX == SpriteData::RIGHT )
  {
    iter = std::find_if(keys.begin(), keys.end(), isWalkingRightPressed);
  }
  else
  {
	iter = std::find_if(keys.begin(), keys.end(), isWalkingLeftPressed);
  }

  if ( iter == keys.end() )
  {
	return Key();
  }

  return *iter;
}

void InputMapping::Keyboard::updateStateKeys(InputMapping::MappedInput& inputs)
{
  std::list<InputMapping::Key>::iterator iter = keys.begin();
  Uint8 *keystate = SDL_GetKeyState(NULL);

  iter++;

  bool anyKeyIsPressed = false;

  for ( iter; iter != keys.end(); iter++)
  {
    bool keyStateIterButton = checkKeyState(keystate[iter->button]);
    if( !iter->isPressed && keyStateIterButton )
    {
      iter->isPressed = true;
      iter->isReleased = false;
      iter->wasPreviouslyPressed = false;
      anyKeyIsPressed = true;
    }
    else if( iter->isPressed && !keyStateIterButton )
    {
      iter->isPressed = false;
      iter->isReleased = true;
      iter->wasPreviouslyPressed = true;
    }
    else
    {
      if ( iter->isPressed = keyStateIterButton )
      {
        anyKeyIsPressed = true;
      }

      iter->isReleased = false;  
      iter->wasPreviouslyPressed = true;
    }

    parseRawInput(*iter, inputs);
    setRawButtonState(*iter, inputs);
  }

  if ( !anyKeyIsPressed )
  {
    iter = keys.begin();
    parseRawInput(*iter, inputs);
    setRawButtonState(*iter, inputs);
  }
}

bool InputMapping::Keyboard::checkKeyState(Uint8 key)
{
  if ( key )
  {
    return true;
  }

  return false;
}