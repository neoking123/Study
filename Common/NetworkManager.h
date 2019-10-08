#pragma once
#include <map>
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

class NetworkManager
{
private:
	static NetworkManager* instance;
	map<SOCKET, USER_INFO*> connectedUsers;
	SOCKET clientSocket;
	int userIndex;

	NetworkManager();
	bool ProcessClientPacket(PACKET_INFO* packet, char * buf, int & len);
	bool ProcessServerPacket(PACKET_INFO* packet, char * buf, int & len);

public:
	~NetworkManager();
	void Init();
	void Release();
	void SetClientSocket(SOCKET clientSocket);
	void ProcessClientReceive(PACKET_INFO* packet, char * buf, int & len);
	void ProcessServerReceive(PACKET_INFO* packet, char * buf, int & len);
	void AddUser(SOCKET clientSocket);
	void SendCreateRoom(string roomName, int playerIndex);
	void SendEnterRoom(int roomNum, int playerIndex);
	void SendRoomState(int roomNum, bool isStart = false, bool canStart = false);
	void SendBackToLobby(int playerIndex, int roomNum);
	void SendLogin(SOCKET clientSocket);
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

