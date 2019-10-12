#pragma once
#include <map>
#include <mutex>
#include "Room.h"
using namespace std;

class Room;

class LobbyManager
{
private:
	static LobbyManager* instance;
	static std::mutex mutex;

	HWND hChat;
	SOCKET sock;
	bool isCreateRoom;
	int roomNum;
	int roomCount;
	int maxRoomNum;
	int roomAlignCount;
	map<int, Room*> rooms;

	LobbyManager();
	void DrawBackground(HDC hdc);
	void DrawRooms(HDC hdc);
	void DrawRoomCreateButton(HDC hdc);
	void UpdateRooms();

public:
	~LobbyManager();

	void Init(HWND hWnd, HINSTANCE g_hInst);
	void Update();
	void Render(HDC hdc);
	void Release();
	void CheckIsClickedRoomCB(int x, int y);
	void CheckIsClickedRoom(int x, int y);
	void ClearRooms();
	void CreateRoom(int roomNum, string roomName, int inPlayerNum = 0);
	void SetInPlayer(int roomNum, int* inPlayer);
	void SetIsStart(int roomNum, bool isStart);
	int GetRoomNum(int playerIndex);
	bool CheckIsRoomMaster(int playerIndex);
	bool GetIsStart(int roomNum);
	bool GetCanStart(int roomNum);
	void SetCanStart(int roomNum, bool canStart);

	inline int GetRoomNum()
	{
		return roomNum;
	}

	inline void SetRoomNum(int roomNum)
	{
		this->roomNum = roomNum;
	}

	inline int GetRoomCount()
	{
		return roomCount;
	}

	inline void SetRoomCount(int roomCount)
	{
		this->roomCount = roomCount;
		mutex.unlock();
	}

	inline int GetMaxRoomNum()
	{
		return maxRoomNum;
	}

	inline void SetMaxRoomNum(int maxRoomNum)
	{
		this->maxRoomNum = maxRoomNum;
		mutex.unlock();
	}

	inline int GetRoomAlignCount()
	{
		return roomAlignCount;
	}

	inline void SetRoomAlignCount(int roomAlignCount)
	{
		this->roomAlignCount = roomAlignCount;
		mutex.unlock();
	}
	
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

	inline static LobbyManager* GetInstanceLock()
	{
		if (instance == nullptr)
		{
			instance = new LobbyManager();
		}
		mutex.lock();
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

