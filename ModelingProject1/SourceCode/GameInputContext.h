#pragma once

#include <map>

#include "RawInputConstants.h"
#include "InputConstants.h"

namespace InputMapping
{
  class GameInputContext
  {
    public:
	 GameInputContext(const std::string filename);
	 ~GameInputContext(void);
	
	 bool mapButtonToAction(RawInputButton button, Action& outActiveAction) const;
	 bool mapButtonToState(RawInputButton button, State& outActiveState) const;

    private:
	 std::map<RawInputButton, Action> actionMap;
	 std::map<RawInputButton, State> stateMap;
  };
}

