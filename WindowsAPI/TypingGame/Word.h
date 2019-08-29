#pragma once
#include "Utility.h"

class Word
{
private:
	string word;
	string prevWord;
	RECT box;
	int speedY;
	Utility::Position position;
	Utility::ITEM item;

public:
	Word();
	Word(string* _word, int _x, int _y, int speed, Utility::ITEM _item);
	~Word();

	void MoveDown();
	void SetSpeedY(int newSpeedY);
	string GetWord();
	string GetPrevWord();
	Utility::Position GetPosition();
	Utility::ITEM GetItem();
	RECT GetBox();
	bool IsOutBoundary();
	void MakeToStar();
	void SetBackWord();
};

