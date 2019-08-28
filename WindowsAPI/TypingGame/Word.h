#pragma once
#include "Utility.h"

struct Position
{
	int x = 0;
	int y = 0;
};

class Word
{
private:
	std::string word;
	Position position;

public:
	Word();
	Word(std::string* _word ,int _x, int _y);
	~Word();

	string* GetWord();
};

