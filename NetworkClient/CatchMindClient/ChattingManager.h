#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
using namespace std;

#define ID_EDIT_0 100
#define ID_EDIT_1 101
#define ID_EDIT_2 102

/**
* @brief 채팅을 관리하는 매니저
* @details 서버로 부터 받은 채팅을 관리한다
* @author Dayeol Hyeon
*/

class ChattingManager
{
private:
	static ChattingManager* instance;

	HWND hWnd;
	char chat[128];
	string chatList;
	float returnInputTime;

	ChattingManager();

public:
	HWND hChat;
	HWND hChatList;

	~ChattingManager();

	void Init(HWND hWnd, HINSTANCE g_hInst);
	void Input();
	void DrawChat(HDC hdc);
	void PrintChat(int playerIndex, string chat);
	void PrintAnswer(int playerIndex, string answer);

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

