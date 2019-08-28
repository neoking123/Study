#include "Word.h"

Word::Word()
{
}

Word::Word(string* _word, int _x, int _y, int speed)
{
	word = *_word;
	position.x = _x;
	position.y = _y;
	box = { position.x - 50, position.y - 10, position.x + 50, position.y + 10};
	speedY = speed;
}

Word::~Word()
{
}

void Word::MoveDown()
{
	position.y += speedY;
	box = { position.x - 50, position.y - 10, position.x + 50, position.y + 10 };
}

void Word::SetSpeedY(int newSpeedY)
{
	speedY = newSpeedY;
}

string Word::GetWord()
{
	return word;
}

Utility::Position Word::GetPosition()
{
	return position;
}

RECT Word::GetBox()
{
	return box;
}

bool Word::IsOutBoundary()
{
	if (position.y > 1000)
	{
		return true;
	}
	else
		return false;
}