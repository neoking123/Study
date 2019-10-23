#pragma once
#include <Windows.h>
#include <string>
using namespace std;

/**
* @brief 비트맵 클래스
* @details bmp파일을 로드하여 관리하는 객체
* @details bmp파일의 사이즈를 반환하거나 들고 있는 bmp파일을 출력한다
* @author Dayeol Hyeon
*/

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

