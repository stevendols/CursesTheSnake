#pragma once
#include<curses.h>
#include<list>
#include<iterator>
#include<iostream>
#include"Windows.h"
#include <ctime>
//#include<conio.h>
using namespace std;

class Snake
{
public:
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		STOP
	};

	std::clock_t start;

	Snake(WINDOW * p, WINDOW * h);
	
	list<pair<int, int>> GetSnake();
	void AddBody(int y, int x);
	bool Collide();
	void Move();
	void Start();
	void SetFruit();

	void UpdateHighScore(int scoreIn, int timeIn);

	int getHighScore();
	int getHighDuration();

private:
	int speed;
	int sheight;
	list < pair<int, int>> body;
	WINDOW * play;
	WINDOW * swin;
	Direction currentDir;	
	pair<int, int> fruit;
	int score, highScore;
	int duration, highDuration;
};