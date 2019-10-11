#pragma once
//#include <WinSock2.h>
#include <map>
#include <vector>
#include "Macro.h"
#include "CatchMindPacket.h"
using namespace std;

class USER_INFO
{
public:
	PACKET_INFO userPacket;
	int index;
	char userName[128];
	int inRoomNum = -1;
};

class ROOM_INFO
{
public:
	char roomName[128];
	int inPlayerNum;
	int inPlayers[MAX_ROOM_IN_NUM] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	bool isStart = false;
	bool canStart = false;
	vector<BRUSH_DATA*> mouseTrack;
	//int board[8][8];
	//int spectators[MAX_SPEC_NUM];
	//int roomNameLen;
};

class NetworkManager
{
private:
	static NetworkManager* instance;
	map<SOCKET, USER_INFO*> connectedUsers;
	map<int, ROOM_INFO*> createdRooms;
	SOCKET clientSocket;
	int userIndex;
	int roomNum;

	NetworkManager();
	SOCKET GetPlayerSocket(int playerIndex);
	int GetRoomNum(int playerIndex);

public:
	~NetworkManager();
	void Init();
	void Release();
	void SetClientSocket(SOCKET clientSocket);
	void AddUser(SOCKET clientSocket);
	void SendCreateRoom(string roomName, int playerIndex);
	void SendEnterRoom(int roomNum, int playerIndex);
	void SendRoomState(int roomNum, bool isStart = false, bool canStart = false);
	void SendBackToLobby(int playerIndex, int roomNum);
	void SendLogin(SOCKET clientSocket);
	void SendChat(int playerIndex, int roomNum, char* chat);
	void SendDrawToServer(int roomNum, BRUSH_DATA& brushData);
	void SendDrawToClient(int roomNum);
	void SendSketchBookToEnterUser(int roomNum, int playerIndex);
	void BroadCastLobbyData();
	void SendChatToRoom(PACKET_CHAT& packet);
	bool CreateRoom(PACKET_CREATE_ROOM packet);
	void EnterRoom(int roomNum, int playerIndex);
	void BackToLobby(int roomNum, int playerIndex);
	void EndUser(SOCKET clientSocket);
	void DrawToSketchBook(int roomNum, BRUSH_DATA brushData);
	PACKET_INFO* GetUserPacket(SOCKET clientSocket);

	static NetworkManager* GetInstance()
	{
		if(instance == nullptr)
		{
			instance = new NetworkManager();
		}
		return instance;
	}

	static void FreeInstance()
	{
		if (instance != nullptr)
		{
			SAFE_DELETE(instance);
		}
	}
};

