#pragma once

enum GameStates 
{
	STATE_NULL,
	STATE_INTRO, 
	STATE_MAINMENU, 
	STATE_LEVELZEROTUTORIAL, 
	STATE_EXIT,
};

class GameState
{
public:
	virtual void handleEvents() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~GameState(){};
};

