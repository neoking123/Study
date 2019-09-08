#pragma once
#include <windows.h>

class BitMap;

class Sprite
{
public:
	BitMap* bitmap;

public:
	Sprite();
	~Sprite();
	void Init(BitMap* bitmap);
	void Draw(HDC gameDC, int x , int y);
};

