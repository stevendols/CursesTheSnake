#include <curses.h>
#include "CursesManager.h"
#include "StateMachine.h"
#include "Snake.h"
#include <iostream>
using namespace std;

int main()
{
	CursesManager curses;

	curses.init();

	//create the state machine
	StateMachine sm;


	

	//Create Menu and play windows
	WINDOW* menu = newwin(curses.getMaxY(), curses.getMaxX(), 0, 0);
	
	//create snake
	Snake snake(play);

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

	//
	

	//listen for a key on the given window
	int key = 0;
	int y, x;
	bool cont = true;

	while (cont)
	{
		wrefresh(menu);
		key = wgetch(menu);
		
		//update the state manager or reset the prompt based on input
		switch (key)
		{
			case (int)'P':
			{
				sm.updateState(sm.PLAY);
				WINDOW * thisplay = newwin(0, 0, 0, 0);
				Snake stemp(thisplay);
				stemp.Start();
				delwin(thisplay);
				sm.SetUpMenu(menu);
				break;
			}
			case (int)'p': 
			{
				sm.updateState(sm.PLAY);
				WINDOW * thisplay = newwin(0, 0, 0, 0);
				Snake stemp(thisplay);
				stemp.Start();
				delwin(thisplay);
				sm.SetUpMenu(menu);
				break; 
			}
			case (int)'H': sm.updateState(sm.HIGHSCORE);
				break;
			case (int)'h': sm.updateState(sm.HIGHSCORE);
				break;
			case (int)'T': sm.updateState(sm.BESTTIME);
				break;
			case (int)'t': sm.updateState(sm.BESTTIME);
				break;
			case (int)'Q': cont = false;
				break;
			case (int)'q': cont = false;
				break;
			default: 
			{
				wmove(menu, 18, 40);
				wclrtobot(menu);
				mvwprintw(menu, 18, 40, "Not an Option, Select a New Option! ");
				wrefresh(menu);
			}

			
		}

		key = 0;
	}
	
	
	//end program
	endwin();
	return 0;
	
}