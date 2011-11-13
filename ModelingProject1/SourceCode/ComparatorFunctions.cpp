
#include "ComparatorFunctions.h"
#include "GameInputContext.h"

bool isWalkingKeyRightPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_RIGHT;
}

bool isWalkingKeyLeftPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_LEFT;
}

bool isRunningKeyPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_Z;
}

bool isJumpingKeyPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_LSHIFT;
}

bool isFastAttackKeyPressed(InputMapping::Key key)
{
  return key.button == InputMapping::RAW_INPUT_BUTTON_X;
}