#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
using namespace std;

#define ID_EDIT_0 100
#define ID_EDIT_1 101

class ChattingManager
{
private:
	static ChattingManager* instance;

	HWND hWnd;
	char chat[128];
	string chatList;
	float returnInputTime;

	ChattingManager();
	void SendChat();

public:
	HWND hChat;
	HWND hChatList;

	~ChattingManager();

	void Init(HWND hWnd, HINSTANCE g_hInst);
	void Input();
	void DrawChat(HDC hdc);
	void PrintChat(int playerIndex, string chat);

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

