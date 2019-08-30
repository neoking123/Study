#include "BitMap.h"

BitMap::BitMap()
{
}


BitMap::~BitMap()
{
}

void BitMap::Init(HDC hdc, HINSTANCE hInst, int id)
{
	hMemDC = CreateCompatibleDC(hdc);
	hBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(id));
	hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);
}

void BitMap::Draw(HDC hdc, HWND hWnd,int x, int y, int width, int height)
{
	BitBlt(hdc, x, y, x + width, y + height, hMemDC, 0, 0, SRCCOPY);
}

void BitMap::Release()
{
	SelectObject(hMemDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(hMemDC);
}
