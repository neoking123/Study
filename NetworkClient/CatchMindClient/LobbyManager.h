#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include "Room.h"
using namespace std;

class Room;

class LobbyManager
{
private:
	static LobbyManager* instance;

	HWND hChat;
	SOCKET sock;
	bool isCreateRoom;

	LobbyManager();
	void DrawBackground(HDC hdc);
	void DrawRooms(HDC hdc);
	void DrawRoomCreateButton(HDC hdc);
	void UpdateRooms();

public:
	int roomNum;
	int roomCount;
	int maxRoomNum;
	map<int, Room*> rooms;

	~LobbyManager();

	void Init(HWND hWnd, HINSTANCE g_hInst);
	void Update();
	void Render(HDC hdc);
	void Release();
	void CheckIsClickedRoomCB(int x, int y);
	void CheckIsClickedRoom(int x, int y);
	void ClearRooms();
	void CreateRoom(string roomName, int inPlayerNum = 0);
	void SetInPlayer(int roomNum, int inPlayer0, int inPlayer1);
	void SetIsStart(int roomNum, bool isStart);
	int GetRoomNum(int playerIndex);
	bool CheckIsRoomMaster(int playerIndex);
	bool GetIsStart(int roomNum);
	bool GetCanStart(int roomNum);
	void SetCanStart(int roomNum, bool canStart);
	
	inline void ActivateCreateRoom()
	{
		isCreateRoom = false;
	}

	inline HWND GetChatHandle()
	{
		return hChat;
	}

	inline static LobbyManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new LobbyManager();
		}
		return instance;
	}

	inline static void FreeInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
};

