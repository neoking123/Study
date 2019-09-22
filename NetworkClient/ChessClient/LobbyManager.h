#pragma once
#include <Windows.h>
#include <list>
#include <string>
using namespace std;

class Room;

class LobbyManager
{
private:
	static LobbyManager* instance;

	list<Room*> rooms;
	int roomNum;

	LobbyManager();
	void DrawBackground(HDC hdc);
	void CreateRoom(string roomName);
	void DrawRooms(HDC hdc);
	void DrawRoomCreateButton(HDC hdc);
	void UpdateRooms();

public:
	~LobbyManager();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void CheckIsClickedRoomCB(int x, int y);
	void CheckIsClickedRoom(int x, int y);

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

