#pragma once
#include <Windows.h>
#include "resource.h"

const int WIDTH = 145;
const int HEIGHT = 235;

class BitMap;
class Card;

class CardGame
{
private:
	static CardGame* pInstance;
	CardGame();

	HWND hWnd;
	BitMap* bitMap;

public:
	~CardGame();
	void Init(HWND hWnd, HDC hdc, HINSTANCE hInst);
	void Update();
	void Draw(HDC hdc);
	void Release();

	static CardGame* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new CardGame();
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

