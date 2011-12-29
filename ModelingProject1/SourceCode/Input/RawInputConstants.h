#pragma once

namespace InputMapping
{
  enum RawInputButton
  {
    RAW_INPUT_NO_BUTTON = 0,
    RAW_INPUT_BUTTON_LSHIFT = 304,
    RAW_INPUT_BUTTON_RIGHT = 275,
    RAW_INPUT_BUTTON_LEFT = 276,
    RAW_INPUT_BUTTON_Z = 122,
    RAW_INPUT_BUTTON_X = 120,
	RAW_INPUT_BUTTON_ENTER = 13,
	RAW_INPUT_BUTTON_GP360_A = 4096,
	RAW_INPUT_BUTTON_GP360_X = 16384,
	RAW_INPUT_BUTTON_GP360_RSHOULDER = 512,
	RAW_INPUT_BUTTON_GP360_LEFT = 4,
	RAW_INPUT_BUTTON_GP360_RIGHT = 8,
	RAW_INPUT_BUTTON_GP360_START = 16,
  };

  enum TypeController
  {
	KEYBOARD,
	GAMEPAD,
  };
}