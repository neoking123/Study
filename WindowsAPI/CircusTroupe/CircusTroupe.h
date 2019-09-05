#pragma once
#include <Windows.h>
#include "Utility.h"

class Character;

class CircusTroupe
{
private:
	CircusTroupe();

	static CircusTroupe* pInstance;
	Character* player;

public:
	~CircusTroupe();

	void Init(HWND hWnd, HDC hdc);
	void Draw(HDC hdc);
	void Input(WPARAM wParam, KEY_STATE keyState);
	void Update();
	void Release();

	static CircusTroupe* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new CircusTroupe();
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

