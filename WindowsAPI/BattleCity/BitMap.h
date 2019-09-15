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
	void Draw(HDC hdc, int x, int y);
	void DrawFourDivisions(HDC hdc, int x, int y, SIZE size1, SIZE size2, SIZE size3, SIZE size4, int l1, int t1, int l2, int t2, int l3, int t3, int l4, int t4);
	void Release();
	HBITMAP& GetBitMap();
};

