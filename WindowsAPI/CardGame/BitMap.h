#pragma once
#include <Windows.h>

class BitMap
{
private:
	HDC hMemDC;
	HBITMAP hBitMap;
	HBITMAP hOldBitMap;

public:
	BitMap();
	~BitMap();
	void Init(HDC hdc, HINSTANCE hInst, int id);
	void Draw(HDC hdc, HWND hWnd, int x, int y, int width, int height);
	void Release();
};

