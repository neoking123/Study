#include "Word.h"

Word::Word()
{
	item = Utility::ITEM::NONE;
}

Word::Word(string* _word, int _x, int _y, int speed, Utility::ITEM _item)
{
	word = *_word;
	prevWord = word;
	position.x = _x;
	position.y = _y;
	box = { position.x - 100, position.y - 10, position.x + 100, position.y + 20};
	speedY = speed;
	item = _item;
}

Word::~Word()
{
}

void Word::MoveDown()
{
	position.y += speedY;
	box = { position.x - 100, position.y - 10, position.x + 100, position.y + 20};
}

void Word::SetSpeedY(int newSpeedY)
{
	speedY = newSpeedY;
}

string Word::GetWord()
{
	return word;
}

string Word::GetPrevWord()
{
	return prevWord;
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
	if (position.y > 880)
	{
		return true;
	}
	else
		return false;
}

void Word::MakeToStar()
{
	prevWord = word;
	for (string::iterator iter = word.begin(); iter != word.end(); iter++)
	{
		*iter = '*';
	}
}

void Word::SetBackWord()
{
	word = prevWord;
}

Utility::ITEM Word::GetItem()
{
	return item;
}
