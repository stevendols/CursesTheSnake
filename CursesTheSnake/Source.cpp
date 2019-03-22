#include <curses.h>
#include <iostream>
using namespace std;

int main()
{
	int maxX, maxY;

	//set up PDCurses
	initscr();

	//don't let user type to screen
	noecho();

	//don't show a cursor
	curs_set(false);

	//find screen dimensions
	getmaxyx(stdscr, maxY, maxX);

	//enable color
	start_color();

	//Create Menu
	WINDOW* menu = newwin(maxY, maxX, 0, 0);
	constexpr auto DARKGREEN = 10;
	init_color(DARKGREEN, 0, 100, 0);
	init_pair(1, COLOR_WHITE, DARKGREEN);

	wbkgd(menu, COLOR_PAIR(1));
	wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
	wattron(menu, A_UNDERLINE);
	mvwprintw(menu, 4, 54, "MAIN MENU");
	wattroff(menu, A_UNDERLINE);
	mvwprintw(menu, 7, 53, "P => Play!");
	mvwprintw(menu, 9, 48, "H => View High Score!");
	mvwprintw(menu, 11, 49, "T => View Best Time!");
	mvwprintw(menu, 13, 53, "Q => Quit :(");
	mvwprintw(menu, 18, 50, "Select An Option! ");
	wmove(menu, 18, 70);
	curs_set(true);
	echo();
	wrefresh(menu);

	
	wgetch(menu);
	endwin();
	return 0;
}