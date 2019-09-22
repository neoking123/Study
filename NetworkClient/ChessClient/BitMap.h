#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class BitMap
{
private:
	HDC hMemDC;
	HBITMAP hBitMap;
	HBITMAP hOldBitMap;
	SIZE size;

public:
	BitMap();
	~BitMap();
	void Init(HDC hdc, int id);
	SIZE GetSize();
	void Draw(HDC hdc, int x, int y, int xSize = 1, int ySize = 1);
	void Release();
};

