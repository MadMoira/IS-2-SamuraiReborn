#pragma once

#include <GameInputContext.h>
#include <RawInputConstants.h>

#include <GameInputStructs.h>

namespace InputMapping
{
  class Controller
  {
    public:
	  Controller(){};
     ~Controller();

	 std::list<Key>* getListKeys() { return &keys; }

	 std::map<RawInputButton, GameCoreStates::SpriteState>* getStateMap() { return &stateMap; }

	 void initializeKeys(std::list<Key> listKeys, std::map<RawInputButton, GameCoreStates::SpriteState> mapKeys);

	 Key& getKeyAssociatedToState(int state, int directionX = 0);

	 void setRawButtonState(Key key, MappedInput& inputs);

	 bool checkIfCanCleanStateVector(MappedInput& inputs);
	 void countAndClearStates(MappedInput& inputs);
	 int countStatesInMapper(MappedInput& inputs, int state);
	 bool verifyDoubleTappingForJumping(MappedInput& inputs, GameCoreStates::SpriteState state);
     void pushBackNewState(MappedInput& inputs, int state, int valueButton);
	 
	 virtual void parseRawInput(Key& key, MappedInput& inputs){};
	 virtual Key getKeyDirectionX(int directionX){ return Key(); };
	 virtual void updateStateKeys(MappedInput& inputs){};

    private:
     bool mapButtonToState(RawInputButton button, GameCoreStates::SpriteState& state) const;

    protected:
	 Controller(int id);

     int playerID;
     std::list<Key> keys;
     std::map<RawInputButton, GameCoreStates::SpriteState> stateMap;
  };
}

