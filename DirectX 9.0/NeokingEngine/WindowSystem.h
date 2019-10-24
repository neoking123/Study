#pragma once
#include <Windows.h>
#include "System.h"

class WindowSystem : public System
{
private:
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

	char windowName[256];

public:
	WindowSystem();
	virtual ~WindowSystem();

	void Init();
	void CreateWindow();
	void Release();
};

