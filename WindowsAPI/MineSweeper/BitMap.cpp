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
	string s = "RES\\";
	s += to_string(id);
	s += ".bmp";
	hMemDC = CreateCompatibleDC(hdc);
	//hBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1 + id));
	hBitMap = (HBITMAP)LoadImage(NULL, s.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE| LR_LOADFROMFILE);
	hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);

	// 파일 사이즈 받아오기
	BITMAP bitMap;
	GetObject(hBitMap, sizeof(bitMap), &bitMap);
	size.cx = bitMap.bmWidth;
	size.cy = bitMap.bmHeight;
}

SIZE BitMap::GetSize()
{
	return size;
}

void BitMap::Draw(HDC hdc, int x, int y)
{
	BitBlt(hdc, x, y, x + size.cx, y + size.cy, hMemDC, 0, 0, SRCCOPY);
}

void BitMap::Release()
{
	SelectObject(hMemDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(hMemDC);
}
