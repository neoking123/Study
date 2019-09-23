#pragma once
#include <Windows.h>
#include <map>
#include <string>
using namespace std;

class Room;

class LobbyManager
{
private:
	static LobbyManager* instance;

	SOCKET sock;
	
	LobbyManager();
	void DrawBackground(HDC hdc);
	void DrawRooms(HDC hdc);
	void DrawRoomCreateButton(HDC hdc);
	void UpdateRooms();
	void SendCreateRoom(string roomName);

public:
	int roomNum;
	int roomCount;
	map<int, Room*> rooms;

	~LobbyManager();

	void Init(SOCKET sock);
	void Update();
	void Render(HDC hdc);
	void Release();
	void CheckIsClickedRoomCB(int x, int y);
	void CheckIsClickedRoom(int x, int y);
	void ClearRooms();
	void CreateRoom(string roomName);

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

