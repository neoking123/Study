#pragma once
#include <Windows.h>

const int WIDTH = 145;
const int HEIGHT = 235;

class BitMap;

class Card
{
private:
	BitMap* front;
	BitMap* back;
	POINT position;
	bool isOpen;
	int id;

public:
	Card();
	~Card();

	void Init(BitMap* _front, BitMap* _back, int width, int height, int _id);
	void Draw(HDC hdc);
};

