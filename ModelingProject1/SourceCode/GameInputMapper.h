#pragma once

#include "RawInputConstants.h"
#include "InputConstants.h"

#include <map>
#include <set>
#include <list>
#include <string>

#include <SDL\SDL.h>

class Player;

namespace InputMapping 
{
  struct MappedInput
  {
    std::set<Action> actions;
    std::set<State> states;

    void eatAction(Action action);
    void eatState(State state);
  };

  typedef void (*inputCallback)(MappedInput& inputs, Player& player);
  
  class GameInputContext;
  
  class GameInputMapper
  {
    public:
	 GameInputMapper(void);
	 ~GameInputMapper(void);

     void clearCurrentMappedInput();
     void addCallback(inputCallback callback, int priorityInMultimap);
	 void dispatchInput(Player& player) const;

     void pushContext(const std::string& name);
     void popContext();

	 void convertRawSDLToRawButtons(RawInputButton& button, SDLKey pressedKey);
	 void processNewInput(SDL_Event evento);
     void setRawButtonState(RawInputButton button, bool isButtonPressed);

    private:
     std::map<std::string, GameInputContext*> inputContexts;
     std::list<GameInputContext*> activeContexts;
     std::multimap<int, inputCallback> callbackTable;
     MappedInput currentMappedInput;
     int buttonPreviouslyPressed;

     bool mapButtonToAction(RawInputButton button, Action& action) const;
     bool mapButtonToState(RawInputButton button, State& state) const;
     void mapAndEatButton(RawInputButton button);
  };
}

