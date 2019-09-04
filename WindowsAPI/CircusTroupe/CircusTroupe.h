#pragma once
#include <Windows.h>

class Character;

class CircusTroupe
{
private:
	CircusTroupe();

	static CircusTroupe* pInstance;
	Character* player;

public:
	~CircusTroupe();

	void Init(HWND hWnd, HINSTANCE hInst, HDC hdc);
	void Draw(HDC hdc);
	void Input(WPARAM wParam);
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

