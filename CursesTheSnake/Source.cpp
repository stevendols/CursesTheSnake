#include <curses.h>
#include "CursesManager.h"
#include <iostream>
using namespace std;

int main()
{
	CursesManager curses;

	curses.init();

	

	//Create Menu
	WINDOW* menu = newwin(curses.getMaxY(), curses.getMaxX(), 0, 0);

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
	mvwprintw(menu, 11, 49, "T => View Best Time!");
	mvwprintw(menu, 13, 53, "Q => Quit :(");
	mvwprintw(menu, 18, 50, "Select An Option! ");

	//move the cursor to a spot on the window
	wmove(menu, 18, 70);

	//turn on cursor and allow text to be echoed
	curs_set(true);
	echo();

	//refresh so changes appear
	wrefresh(menu);

	//listen for a key on the given window
	wgetch(menu);

	//end program
	endwin();
	return 0;
}