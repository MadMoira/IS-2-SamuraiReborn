
#include <Windows.h>

#include "Gamepad.h"

#include <SpriteDataConstants.h>
#include <algorithm>

InputMapping::Gamepad::Gamepad(int id) : Controller(id)
{
}

   //DWORD dwResult;    
/*for (DWORD i=0; i< 4; i++ )
{
  XINPUT_STATE state;
  ZeroMemory( &state, sizeof(XINPUT_STATE) );

        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState( i, &state );

		WORD d = state.Gamepad.wButtons;
		if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			dwResult = XInputGetState( i, &state );
					if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			int d = 4;
					}
		}
        if( dwResult == ERROR_SUCCESS )
  { 
      // Controller is connected 
  }
        else
  {
            // Controller is not connected 
  }
}*/

void InputMapping::Gamepad::parseRawInput(InputMapping::Key& key, InputMapping::MappedInput& inputs)
{
  switch(key.button)
  {
    case RAW_INPUT_BUTTON_GP360_RIGHT:  
    {
      key.button = RAW_INPUT_BUTTON_GP360_RIGHT;

      if ( key.isPressed )
      {
        inputs.directionKeyPressed = SpriteData::RIGHT; 
      }
      break;
    }
    case RAW_INPUT_BUTTON_GP360_LEFT:  
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_GP360_LEFT;

      if ( key.isPressed )
      {
        inputs.directionKeyPressed = SpriteData::LEFT; 
      }

      break;
    }
    case RAW_INPUT_BUTTON_GP360_A:  
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_GP360_A;
	  break;
	}
    case RAW_INPUT_BUTTON_GP360_X:  
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_GP360_X;
	  break;
	}
    case RAW_INPUT_BUTTON_GP360_RSHOULDER:  
    {
      key.button = InputMapping::RAW_INPUT_BUTTON_GP360_RSHOULDER;
	  break;
	}
  } 
}

bool isWalkingKRightPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_GP360_RIGHT;
}

bool isWalkingKLeftPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_GP360_LEFT;
}

InputMapping::Key InputMapping::Gamepad::getKeyDirectionX(int directionX)
{
  std::list<InputMapping::Key>::iterator iter;
  if ( directionX == SpriteData::RIGHT )
  {
    iter = std::find_if(keys.begin(), keys.end(), isWalkingKRightPressed);
  }
  else
  {
	iter = std::find_if(keys.begin(), keys.end(), isWalkingKLeftPressed);
  }

  if ( iter == keys.end() )
  {
	return Key();
  }

  return *iter;
}

void InputMapping::Gamepad::updateStateKeys(InputMapping::MappedInput& inputs)
{
  std::list<InputMapping::Key>::iterator iter = keys.begin();

  iter++;

  bool anyKeyIsPressed = false;

  for ( iter; iter != keys.end(); iter++)
  {
    bool keyStateIterButton = checkKeyState(iter->button);

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

bool InputMapping::Gamepad::checkKeyState(WORD button)
{
  DWORD dwResult;    
  for (DWORD i = 0; i < 1; i++ )
  {
    XINPUT_STATE state;
    ZeroMemory( &state, sizeof(XINPUT_STATE) );

    dwResult = XInputGetState( i, &state );

    if ( state.Gamepad.wButtons & button)
    {
	  return true;
	}
  }
  return false;
}