#pragma once
//#include <WinSock2.h>
#include <map>
#include <vector>
#include "Macro.h"
#include "CatchMindPacket.h"
using namespace std;

class PLAYER_INFO
{
public:
	PACKET_INFO playerPacket;
	int index;
	char nickName[128];
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
};

class PLAYER_INFO;

class NetworkManager
{
private:
	static NetworkManager* instance;
	map<SOCKET, PLAYER_INFO*> connectedPlayers;
	map<int, ROOM_INFO*> createdRooms;
	SOCKET clientSocket;
	int userIndex;
	int roomNum;
	int roomCount;

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
	void SendBackToLobby(int roomNum, int playerIndex);
	void SendLoginToClient(SOCKET clientSocket);
	void SendLoginToServer(int playerIndex, char* nickName);
	void SendChat(int playerIndex, int roomNum, char* chat);
	void SendDrawToServer(int roomNum, BRUSH_DATA& brushData);
	void SendDrawToClient(int roomNum);
	void SendSketchBookToEnterUser(int roomNum, int playerIndex);
	void BroadCastLobbyData();
	void BroadCastPlayerData();
	void SendChatToRoom(PACKET_CHAT& packet);
	bool CreateRoom(PACKET_CREATE_ROOM packet);
	void EnterRoom(int roomNum, int playerIndex);
	void BackToLobby(int roomNum, int playerIndex);
	void EndUser(SOCKET clientSocket);
	void DrawToSketchBook(int roomNum, BRUSH_DATA brushData);
	void SetNickName(int playerIndex, char* nickName);
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

