#include "snake.h"
#include <string>
#include<vector>


# define SNAKECOL 2
# define APPLECOL 3
# define BACKCOL 4

Snake::Snake(WINDOW * p, WINDOW * scoreside, ScoreHold * hist)
{
	play = p;
	swin = scoreside;

	start = std::clock();
	
	currentDir = UP;
	speed = 80;
	score = 0;

	if (can_change_color()) {
		//set colors
		//init_color(COLOR_MAGENTA, 627, 321, 176);
		//init_color(COLOR_RED, 1000, 0, 0);
		//init_color(COLOR_MAGENTA, 1000, 411, 705);
		init_pair(APPLECOL, COLOR_RED, COLOR_WHITE);
		//init_pair(SNAKECOL, COLOR_)
		init_pair(BACKCOL, COLOR_BLUE, COLOR_WHITE);
		wbkgd(play, COLOR_PAIR(BACKCOL));
	}
	scoreHist = hist;
}

//return a vector of y,x positions for the snake's body
list<pair<int, int>> Snake::GetSnake()
{
	return body;
}

//move the player
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
		score++;
		//CheckScoreChange();
		/*const char * stemp = to_string(score).c_str();
		mvwprintw(play, 30, 30, stemp);*/
		//wrefresh(play);
		SetFruit();
	}
	
	
	bool collide = false;
	int dumbcount = 0;
	for (pair<int, int> it : body)
	{
		if (it == body.back() && dumbcount < body.size()-1)
		{
			collide = true;
		}
		dumbcount++;
	}
	
	if (collide)
	{
		currentDir = STOP;
	}

	

	int maxx, maxy;
	getmaxyx(play, maxy, maxx);

	if (x <= 0 || y <= 0 || x >= (maxx-1) || y >= (maxy-1))
	{
		currentDir = STOP;
	}
	//Collide();

	getmaxyx(swin, maxy, maxx);
	int point = 2;
	string ko = "Score: ";
	ko += to_string(score);

	string time = "Seconds Alive: ";
	duration = (std::clock() - start) / CLOCKS_PER_SEC;
	time += to_string(duration);

	//CheckTimeChange();
	
	mvwaddstr(swin, 3, 3, ko.c_str());
	mvwaddstr(swin, 9, 3, time.c_str());
	wrefresh(swin);
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
	curs_set(0); //This did cause an error when moving left, but is not now
	currentDir = UP;
	cbreak();
	noecho();

	SetFruit();

	int ysize, xsize;
	int key = (int)'w';
	sheight = 6;

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

		if (duration > highDuration)
			highDuration = duration;
		
		
		wrefresh(play);

		if (currentDir == RIGHT || currentDir == LEFT)
			Sleep(speed*.5);//speedFactor*1.4);
		else
			Sleep(speed);

	} while (key != 2 && currentDir != STOP);

	vector<int> shist = scoreHist->GetHighScores();

	//string getname = "Please write a 5 character name: ";

	//add to high score if neccessary
	if (shist.size() < 5 || score > shist[4])
	{
		scoreHist->AddHighScore(score);
	}

	//
		/*wclear(play);
		wattron(play, A_UNDERLINE);
		string winmessage = "CONGRATULATIONS, YOU HAVE SET A HIGH SCORE!"; 
		mvwprintw(play, (int)LINES*.75, COLS / 2 - winmessage.size() / 2, winmessage.c_str());
		mvwprintw(play, (int)LINES*.25, COLS / 2 - getname.size() / 2, getname.c_str());
		echo();
		nodelay(play, true);
		nocbreak();
		string inname;
		do
		{
			int xpos, ypos;
			getyx(play, ypos, xpos);
			for (int j = 1; j <= inname.size()+1; j++)
			{
				mvwaddch(play, ypos, xpos - j, '_');
			}
			inname = wgetch(play);
		} while (inname.size() > 5);
	}*/


	//add to high times if neccessary
	vector<int> thist = scoreHist->GetHighTimes();
	if (thist.size() < 5 || duration > thist[4])
	{
		scoreHist->AddHighTime(duration);
	}


	wclear(play);
	//wrefresh(play);
	//nodelay(play, false);
	///curs_set(1);
	//nocbreak();
	//echo();
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
	wattron(play, COLOR_PAIR(APPLECOL));
	mvwaddch(play, yloc, xloc, 'A');
	wattroff(play, COLOR_PAIR(APPLECOL));
	//wrefresh(play);
}

void Snake::UpdateHighScore(int scoreIn, int timeIn)
{
	highScore = scoreIn;
	highDuration = timeIn;

	file.open("Score.txt");
	file << scoreIn;
	file.close();
}

int Snake::getHighScore()
{
	return highScore;
}

int Snake::getHighDuration()
{
	return highDuration;
}

//return the high score stored in the file
int Snake::GetLastHighScore()
{
	//open the file with the score
	file.open("Score.txt");
	int currentHigh;
	//string tempScore;
	file >> currentHigh;

	//use stringstream to convert the string ot an integer
	//stringstream tscore(tempScore);
	file.close();
	return currentHigh;
}

//check if the current score is better than the score in the file. If it is, change the file
void Snake::CheckScoreChange()
{
	int currentScore = GetLastHighScore();
	if (score > currentScore)
	{
		file.open("Score.txt");
		file << score;
		file.close();
	}
}

int Snake::GetLastHighTime()
{
	//open the file with the time
	file.open("Time.txt");
	int currTime;
	//string tempScore;
	file >> currTime;

	//use stringstream to convert the string ot an integer
	//stringstream tscore(tempScore);
	file.close();
	return currTime;
}

void Snake::CheckTimeChange()
{
	int currentTime = GetLastHighTime();

	if (duration > currentTime)
	{
		file.open("Time.txt");
		file << duration;
		file.close();
	}
}
