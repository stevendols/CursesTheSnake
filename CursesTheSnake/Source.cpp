#include <curses.h>

int main()
{
	int maxX, maxY;
	initscr();
	noecho();
	curs_set(false);

	getmaxyx(stdscr, maxY, maxX);

	WINDOW* win1 = newwin(maxY, maxX, 0, 0);
	WINDOW* win2 = newwin(maxY, maxX, 0, 0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	wbkgd(win1, COLOR_PAIR(1));
	wprintw(win1, "TEST");
	
	init_pair(2, COLOR_BLACK, COLOR_RED);
	wbkgd(win2, COLOR_PAIR(2));
	wprintw(win2, "TEST 2");

	wrefresh(win1);
	wgetch(win1);
	wrefresh(win2);
	wgetch(win2);

	endwin();
	return 0;
}