#include "BitMap.h"

BitMap::BitMap()
{
}


BitMap::~BitMap()
{
}

void BitMap::Init(HDC hdc, int id)
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

//void BitMap::Draw(HDC hdc, int x, int y)
//{
//	BitBlt(hdc, x, y, x + size.cx, y + size.cy, hMemDC, 0, 0, SRCCOPY);
//	
//}

void BitMap::Draw(HDC hdc, int x, int y)
{
	TransparentBlt(hdc, x, y, size.cx, size.cy, hMemDC, 0, 0, size.cx, size.cy, RGB(255, 0, 255));
}

void BitMap::DrawFourDivisions(HDC hdc, int x, int y, SIZE size1, SIZE size2, SIZE size3, SIZE size4, int l1, int t1, int l2, int t2, int l3, int t3, int l4, int t4)
{
	TransparentBlt(hdc, x + l1, y + t1, size1.cx, size1.cy, hMemDC, l1, t1, size1.cx, size1.cy, RGB(255, 0, 255));
	TransparentBlt(hdc, x + l2, y + t2, size2.cx, size2.cy, hMemDC, l2, t2, size2.cx, size2.cy, RGB(255, 0, 255));
	TransparentBlt(hdc, x + l3, y + t3, size3.cx, size3.cy, hMemDC, l3, t3, size3.cx, size3.cy, RGB(255, 0, 255));
	TransparentBlt(hdc, x + l4, y + t4, size4.cx, size4.cy, hMemDC, l4, t4, size4.cx, size4.cy, RGB(255, 0, 255));
}

void BitMap::Release()
{
	SelectObject(hMemDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(hMemDC);
}
