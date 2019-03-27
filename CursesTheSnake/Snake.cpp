#include "snake.h"
#include <string>

Snake::Snake(WINDOW * win)
{
	play = win;
	//create a border (left, right, top, bottom, four corners
	wborder(play, '|', '|', '-', '-', '+', '+', '+', '+');
	currentDir = UP;
	speed = 80;
	score = 0;
}

//return a vector of y,x positions for the snake's body
list<pair<int, int>> Snake::GetSnake()
{
	return body;
}

void Snake::Move()
{
	cout << "move";
	int x = body.back().second;
	int y = body.back().first;

	switch (currentDir)
	{
	case UP: 
		y--;
		break;
	case DOWN: 
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}
	body.push_back(pair<int, int>(y, x));
	mvwaddch(play, y, x, '@');
	wrefresh(play);

	if (x != fruit.second || y != fruit.first)
	{
		
		mvwaddch(play, body.front().first, body.front().second, ' ');
		wrefresh(play);
		body.pop_front();
	}
	else
	{
		/*score++;
		const char * stemp = to_string(score).c_str();
		mvwprintw(play, 30, 30, stemp);*/
		//wrefresh(play);
		SetFruit();
	}
	
	bool collide = false;
	for (pair<int, int> it : body)
	{
		if (y == it.first && x == it.second && it != body.back())
		{
			collide = true;
		}
	}
	
	if (collide)
	{
		currentDir = STOP;
	}

	if (x <= 0 || y <= 0 || x >= COLS || y >= LINES)
	{
		currentDir = STOP;
	}
	Collide();
}

//Check if snake hit itself
bool Snake::Collide()
{
	for (pair<int,int> it: body)
	{
		if (body.back().first == it.first && body.back().second == it.second && it != body.back())
		{
			return true;
		}
	}

	return false;
}

void Snake::AddBody(int y, int x)
{
	body.push_back(pair<int, int>(y, x));
	mvwaddch(play, y, x, '@');
}

void Snake::Start()
{
	//curs_set(0); This causes errors when moving left, but should hide the cursor
	cbreak();
	noecho();

	currentDir = UP;

	SetFruit();

	int ysize, xsize;
	int key = (int)'w';

	//set cursor in center
	getmaxyx(play, ysize, xsize);
	wmove(play, ysize / 2, xsize / 2);
	AddBody(ysize / 2, xsize / 2);
	float speedFactor = (float)ysize / xsize;

	wrefresh(play);
	nodelay(play, true);

	//take in user input and set direction
	do
	{
		key = wgetch(play);
		switch (key)
		{
			case (int)'a': 
				if (currentDir != RIGHT)
					currentDir = LEFT;
				break;
			case (int)'w': 
				if (currentDir != DOWN)
					currentDir = UP;
				break;
			case (int)'d': 
				if (currentDir != LEFT)
					currentDir = RIGHT;
				break;
			case (int)'s': 
				if (currentDir != UP)
					currentDir = DOWN;
				break;
			case 27: currentDir = STOP;
				break;
		}

		Move();

		//check bounds
		//if (body.)
		
		wrefresh(play);

		if (currentDir == RIGHT || currentDir == LEFT)
			Sleep(speed*speedFactor*1.4);
		else
			Sleep(speed);

	} while (key != 2 && currentDir != STOP);

	wclear(play);
	wrefresh(play);
	/*nodelay(play, false);
	curs_set(1);
	nocbreak();
	echo();*/
}

void Snake::SetFruit()
{
	int x, y, xloc, yloc;

	getmaxyx(play, y, x);

	bool cont = false;

	do
	{
		cont = false;
		yloc = rand() % (y-1);
		xloc = rand() % (x-1);

		for (pair<int, int> it : body)
		{
			if (yloc == it.first && xloc == it.second)
			{
				cont = true;
			}
		}
	} while (cont || xloc == 0 || yloc == 0);

	fruit = pair<int, int>(yloc, xloc);
	mvwaddch(play, yloc, xloc, 'A');
	//wrefresh(play);
}

