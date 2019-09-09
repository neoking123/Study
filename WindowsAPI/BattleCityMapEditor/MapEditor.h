#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class MapEditor
{
private:
	MapEditor();

	static MapEditor* pInstance;

	HWND hWnd;
	HDC editorDC;
	HBITMAP hBitMap;
	HBITMAP hOldBitMap;
	SIZE editorSize;
	vector<HWND> hRadios;

	void CreateRadioButton(HWND hWnd, HINSTANCE g_hInst);

public:
	~MapEditor();

	void Init(HDC hdc, HWND hWnd, HINSTANCE g_hInst, SIZE editorSize);
	void Draw(HDC hdc);
	void Update();
	void Release();

	static MapEditor* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new MapEditor();
		}
		return pInstance;
	}

	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
};

