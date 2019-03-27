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

void StateMachine::SetUpMenu(WINDOW * win)
{
	//create darkgreen color as color #10
	constexpr auto DARKGREEN = 10;
	init_color(DARKGREEN, 0, 100, 0);

	//pair 1 = white text on darkgreen background
	init_pair(1, COLOR_WHITE, DARKGREEN);

	//set menu window's background to pair 1
	wbkgd(win, COLOR_PAIR(1));
	//create a border (left, right, top, bottom, four corners
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

	//set underlined text
	wattron(win, A_UNDERLINE);
	//print text on menu window
	mvwprintw(win, 4, 54, "MAIN MENU");
	//turn off underlined text
	wattroff(win, A_UNDERLINE);

	//print text on main window
	//args(window name, y, x, text)
	mvwprintw(win, 7, 53, "P => Play!");
	mvwprintw(win, 9, 48, "H => View High Score!");
	mvwprintw(win, 11, 49, "T => View Best Time!");
	mvwprintw(win, 13, 53, "Q => Quit :(");
	mvwprintw(win, 18, 50, "Select An Option! ");

	//move the cursor to a spot on the window
	wmove(win, 18, 70);

	//turn on cursor and allow text to be echoed
	curs_set(true);
	echo();

	//refresh so changes appear
	wrefresh(win);
}
