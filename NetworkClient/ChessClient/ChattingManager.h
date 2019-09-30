#pragma once
#include <Windows.h>

#define ID_EDIT_0 100
#define ID_EDIT_1 101

class ChattingManager
{
private:
	static ChattingManager* instance;

	char chat[128];

	ChattingManager();
	void SendChat();

public:
	HWND hChat;
	HWND hChatList;

	~ChattingManager();

	void Init(HWND hWnd, HINSTANCE g_hInst);
	void Input();
	void DrawChat(HDC hdc);

	static ChattingManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ChattingManager();
		}
		return instance;
	}

	static void FreeInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

};

