#include "CursesManager.h"

CursesManager::CursesManager()
{
}


CursesManager::~CursesManager()
{
}

void CursesManager::init()
{
	//set up PDCurses
	initscr();

	//don't let user type to screen
	noecho();

	//don't show a cursor
	curs_set(false);

	//enable color
	start_color();

	//find screen dimensions
	getmaxyx(stdscr, maxY, maxX);
}

int CursesManager::getMaxX()
{
	return maxX;
}

int CursesManager::getMaxY()
{
	return maxY;
}

