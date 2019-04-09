#include "ScoreHold.h"
//#include <algorithm>

ScoreHold::ScoreHold()
{
	//add the high scores to the vector
	file.open("Score.txt");
	int score;
	while (file >> score)
	{
		scores.push_back(score);
	}
	file.close();

	//add the high times to the vector
	file.open("Time.txt");
	int time;
	while (file >> time)
	{
		times.push_back(time);
	}
	file.close();
}

vector<int> ScoreHold::GetHighScores()
{
	return scores;
}

vector<int> ScoreHold::GetHighTimes()
{
	return times;
}

//called when a new highscore is reached
void ScoreHold::AddHighScore(int newScore)
{
	scores.push_back(newScore);
	//sort(scores.begin(), scores.end(), scores);

	//remove last if greater than 5 scores
	if (scores.size() > 5)
	{
		vector<int> temp;
		for (int i = 0; i < 5; i++)
		{
			temp.push_back(scores[i]);
		}
		scores = temp;
	}
}

//called when a new hightime is reached
void ScoreHold::AddHighTime(int newTime)
{
	if (times.size() == 0)
		times.push_back(newTime);
	else
	{
		bool inserted = false;
		vector<int> temp;
		int length = times.size();
		if (length > 4)
			length = 4;
		for (int i = 0; i < length; i++)
		{
			if (!inserted && newTime > times[i])
			{
				//times[i] = newTime;
				inserted = true;
				temp.push_back(newTime);
			}
			temp.push_back(times[i]);
			
		}
		if (!inserted)
		{
			temp.push_back(newTime);
		}
		times.clear();
		for (int i = 0; i < temp.size(); i++)
		{
			times.push_back(temp[i]);
		}		
	}
}

//Write all info to the two files
void ScoreHold::WriteAll()
{
	//write scores
	if (scores.size() == 0)
	{
		ofstream f;
		int stop;
		f.open("Score.txt", ios::out, ios::trunc);
		f.close();
	}
	else
	{
		file.open("Score.txt");
		for (int i = 0; i < scores.size(); i++)
		{
			file << scores[i] << "\n";
		}
		file.close();
	}

	//write times
	if (times.size() == 0)
	{
		ofstream f;
		f.open("Time.txt", ios::out, ios::trunc);
		f.close();
	}
	else
	{
		file.open("Time.txt");
		for (int i = 0; i < times.size(); i++)
		{
			file << times[i] << "\n";
		}
		file.close();
	}
	
}

//remove all scores
void ScoreHold::ResetAll()
{
	scores.clear();
	times.clear();
}