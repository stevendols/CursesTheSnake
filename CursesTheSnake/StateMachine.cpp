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

void StateMachine::SetUpMenu(WINDOW * menu)
{
	menu = newwin(0, 0, 0, 0);
	//create darkgreen color as color #10
	constexpr auto DARKGREEN = 10;
	init_color(DARKGREEN, 0, 100, 0);

	//pair 1 = white text on darkgreen background
	init_pair(1, COLOR_WHITE, DARKGREEN);

	//set menu window's background to pair 1
	wbkgd(menu, COLOR_PAIR(1));
	//create a border (left, right, top, bottom, four corners
	wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');

	//set underlined text
	wattron(menu, A_UNDERLINE);
	//print text on menu window
	mvwprintw(menu, 4, 54, "MAIN MENU");
	//turn off underlined text
	wattroff(menu, A_UNDERLINE);

	//print text on main window
	//args(window name, y, x, text)
	mvwprintw(menu, 7, 53, "P => Play!");
	mvwprintw(menu, 9, 48, "H => View High Score!");
	mvwprintw(menu, 11, 50, "R => Reset Scores!");
	mvwprintw(menu, 13, 53, "Q => Quit :(");
	mvwprintw(menu, 18, 50, "Select An Option! ");

	//move the cursor to a spot on the window
	wmove(menu, 18, 70);

	//turn on cursor and allow text to be echoed
	curs_set(true);
	//cbreak();
	echo();

	//refresh so changes appear
	wrefresh(menu);
}
