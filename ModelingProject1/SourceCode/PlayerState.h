#pragma once

#include "State.h"
#include "GameInputContext.h"
#include "GameSound.h"

namespace GameCoreStates
{
  struct ConditionsPlayerRunning
  {
	bool directionButtonPressed;
	bool runningButtonPressed;
  };

  class PlayerState : public State
  {
   public:
	PlayerState(int id);
	PlayerState(int id, int charID);
	PlayerState(){};
	~PlayerState(){};

	int checkIfEqualStates(std::list<InputMapping::Key> keys, int currentState,
		                   int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed);
	int checkMovementRestrictions(int keyPreviouslyPressed, int previousState, 
		                          int currentState, std::list<InputMapping::Key> keys);
	ConditionsPlayerRunning checkIfPlayerIsRunning(std::list<InputMapping::Key> keys);

   protected:
	virtual int checkMovement(int keyPreviouslyPressed, int previousState, 
                              int currentState, std::list<InputMapping::Key> keys);
	virtual int checkChangeOfState(std::list<InputMapping::Key> keys, int currentState,
		                   int previousState, GameCoreStates::PlayerState* newState,
                           int keyPreviouslyPressed);
	 int characterID;
  };
}