#pragma once
#include "curses.h"
class StateMachine
{
public:
	enum States
	{
		MAINMENU,
		PLAY,
		PAUSE,
		HIGHSCORE,
		BESTTIME
	};

	StateMachine();
	~StateMachine();

	void updateState(States newState);
	void SetUpMenu(WINDOW * win);

private:
	States currentState;
};

