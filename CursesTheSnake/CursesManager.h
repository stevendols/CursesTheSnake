#pragma once
#include <curses.h>

class CursesManager
{
public:
	CursesManager();
	~CursesManager();
	void init();
	int getMaxX();
	int getMaxY();

private:
	int maxX, maxY;
	
};

