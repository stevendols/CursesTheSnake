#include "StateMachine.h"

StateMachine::StateMachine()
{
	updateState(MAINMENU);
}


StateMachine::~StateMachine()
{
}

void StateMachine::updateState(States newState)
{
	currentState = newState;
}
