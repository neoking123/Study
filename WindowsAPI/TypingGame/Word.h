#pragma once
#include "Utility.h"

class Word
{
private:
	string word;
	RECT box;
	Utility::Position position;
	int speedY;

public:
	Word();
	Word(string* _word, int _x, int _y, int speed);
	~Word();

	void MoveDown();
	void SetSpeedY(int newSpeedY);
	string GetWord();
	Utility::Position GetPosition();
	RECT GetBox();
	bool IsOutBoundary();
};

