#pragma once
#include <string>
using namespace std;

struct Position
{
	int x = 0;
	int y = 0;
};

class Word
{
private:
	string word;
	Position position;

public:
	Word();
	Word(string* _word ,int _x, int _y);
	~Word();

	string* GetWord();
};

