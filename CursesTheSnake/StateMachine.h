#pragma once
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

private:
	States currentState;
};

