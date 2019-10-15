#pragma once
#include <map>
#include <mutex>
#include "Room.h"
#include "..\..\Common\Macro.h"
using namespace std;

struct Player
{
	int inRoomNum;
	int kungyaNum;
	int answerCount;
	char nickName[32];
};

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
	int playerCount;
	map<int, Room*> rooms;
	map<int, Player*> players;

	LobbyManager();
	void DrawBackground(HDC hdc);
	void DrawRooms(HDC hdc);
	void DrawRoomCreateButton(HDC hdc);
	void DrawConnectedPlayers(HDC hdc);
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
	void CreateRoom(int roomNum, string roomName, int inPlayerNum = 0, int roomMasterIndex = -1);
	void SetInPlayer(int roomNum, int* inPlayer, bool* readyState);
	void SetIsStart(int roomNum, bool isStart);
	int GetRoomNum(int playerIndex);
	bool CheckIsRoomMaster(int playerIndex);
	bool GetIsStart(int roomNum);
	bool GetCanStart(int roomNum);
	void SetCanStart(int roomNum, bool canStart);
	void SetPlayers(int playterIndex, char* nickName, int inRoomNum, int kungyaNum);
	void ClearPlayers();
	bool CheckCanStart(int roomNum, int playerIndex);
	void SetAnswerWordInClient(int roomNum, char* answerWord);

	inline char* GetAnswerWord(int roomNum)
	{
		return rooms[roomNum]->answerWord;
	}

	inline int GetCurrentTurn(int roomNum)
	{
		return rooms[roomNum]->curTurn;
	}

	inline void SetCurrentTurn(int roomNum, int curTurn)
	{
		rooms[roomNum]->curTurn = curTurn;
		mutex.unlock();
	}
	
	inline bool CheckIsReady(int roomNum, int i)
	{
		return rooms[roomNum]->reayState[i];
	}

	inline int GetPlayerIndex(int roomNum, int index)
	{
		return rooms[roomNum]->inPlayer[index];
	}

	inline int GetKungyaNum(int playerIndex)
	{
		if (players[playerIndex] != nullptr)
			return players[playerIndex]->kungyaNum;
		else
			return -1;
	}

	inline int GetKungyaNum(int roomNum, int index)
	{
		if (roomNum == -1)
		{
			mutex.unlock();
			return -1;
		}

		if (rooms[roomNum]->inPlayer[index] == -1)
		{
			mutex.unlock();
			return -1;
		}
		else
		{
			mutex.unlock();
			return GetKungyaNum(rooms[roomNum]->inPlayer[index]);
		}
	}

	inline char* GetNickName(int playerIndex)
	{
		if (players[playerIndex] != nullptr)
			return players[playerIndex]->nickName;
		else
			return nullptr;
	}

	inline char* GetNickName(int roomNum, int index)
	{
		if (roomNum == -1)
		{
			mutex.unlock();
			return nullptr;
		}

		if (rooms[roomNum]->inPlayer[index] == -1)
		{
			mutex.unlock();
			return nullptr;
		}
		else
		{
			mutex.unlock();
			return GetNickName(rooms[roomNum]->inPlayer[index]);
		}
	}

	inline int GetPlayerCount()
	{
		return playerCount;
	}

	inline void SetPlayerCount(int playerCount)
	{
		this->playerCount = playerCount;
		mutex.unlock();
	}

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
		SAFE_DELETE(instance);
	}
};

