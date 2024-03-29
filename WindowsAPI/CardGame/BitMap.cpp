#include "BitMap.h"
#include "resource.h"

BitMap::BitMap()
{
}


BitMap::~BitMap()
{
}

void BitMap::Init(HDC hdc, HINSTANCE hInst, int id)
{
	hMemDC = CreateCompatibleDC(hdc);
	//hBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1 + id));
	hBitMap = (HBITMAP)LoadImage(NULL, "00.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE| LR_LOADFROMFILE);

	hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);


	// 파일 사이즈 받아오기
	/*BITMAP bitMap;
	GetObject(hBitMap, sizeof(bitMap), &bitMap);
	size.cx = bitMap.bmWidth;
	size.cy = bitMap.bmHeight;*/
}

void BitMap::Draw(HDC hdc, int x, int y, int width, int height)
{
	BitBlt(hdc, x, y, x + width, y + height, hMemDC, 0, 0, SRCCOPY);
}

void BitMap::Release()
{
	SelectObject(hMemDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(hMemDC);
}
