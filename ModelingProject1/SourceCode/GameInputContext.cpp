
#include "GameInputContext.h"
#include "File.h"

InputMapping::GameInputContext::GameInputContext(const std::string filename)
{
  std::ifstream inputContextFile(filename.c_str());

  unsigned stateCount = readDataTypeFromFile<unsigned>(inputContextFile);
  for(unsigned i = 0; i < stateCount; i++)
  {
	RawInputButton button = static_cast<RawInputButton>(readDataTypeFromFile<unsigned>(inputContextFile));
	State state = static_cast<State>(readDataTypeFromFile<unsigned>(inputContextFile));
	stateMap[button] = state;
  }

  unsigned actionCount = readDataTypeFromFile<unsigned>(inputContextFile);
  for(unsigned i = 0; i < actionCount; i++)
  {
    RawInputButton button = static_cast<RawInputButton>(readDataTypeFromFile<unsigned>(inputContextFile));
	Action action = static_cast<Action>(readDataTypeFromFile<unsigned>(inputContextFile));
	actionMap[button] = action;
  }
}

InputMapping::GameInputContext::~GameInputContext(void)
{
}

bool InputMapping::GameInputContext::mapButtonToAction(RawInputButton button, 
	                                                   Action& outActiveAction) const
{
  std::map<RawInputButton, Action>::const_iterator iter = actionMap.find(button);
  
  if( iter == actionMap.end() )
  {
    return false;
  }

  outActiveAction = iter->second;
  return true;
}

bool InputMapping::GameInputContext::mapButtonToState(RawInputButton button, 
	                                                  State& outActiveState) const
{
  std::map<RawInputButton, State>::const_iterator iter = stateMap.find(button);

  if( iter == stateMap.end() )
  {
    return false;
  }

  outActiveState = iter->second;
  return true;
}

