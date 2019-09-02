#pragma once
#include <Windows.h>

const int WIDTH = 30;
const int HEIGHT = 16;

class MineSweeper
{
private:
	static MineSweeper* pInstance;

	MineSweeper();
	HWND hWnd;
	SIZE size;

public:
	~MineSweeper();

	void Init(HDC hdc, HINSTANCE hInst, HWND hWnd);
	void Release();
	void Draw(HDC hdc);
	void Update();
	void Input(POINT pt);
	void DrawBackground(HDC hdc);
	void SendGamOverMessage();
	SIZE GetSize();

	static MineSweeper* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new MineSweeper();
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

