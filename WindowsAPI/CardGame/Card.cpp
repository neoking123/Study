#include "Card.h"
#include "BitMap.h"

Card::Card()
{
}


Card::~Card()
{
}

void Card::Init(BitMap* _front, BitMap* _back, int x, int y, int _id)
{
	front = _front;
	back = _back;
	position.x = x;
	position.y = y;
	id = _id;
	isOpen = true;
}

void Card::Draw(HDC hdc)
{
	if (isOpen)
	{
		front->Draw(hdc, position.x, position.y, WIDTH, HEIGHT);
	}
	else
	{
		back->Draw(hdc, position.x, position.y, WIDTH, HEIGHT);
	}
}