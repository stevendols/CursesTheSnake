#pragma once
#include <curses.h>
#include <vector>
#include <fstream>
//#include <ifstream>
using namespace std;

//class to store the scores and write them
class ScoreHold
{
public:
	ScoreHold();

	vector<int> GetHighScores();
	vector<int> GetHighTimes();

	void AddHighTime(int newTime);
	void AddHighScore(int newScore);
	void WriteAll();
	void ResetAll();

private:
	vector<int> scores;
	vector<int> times;
	fstream file;
};
