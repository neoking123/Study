#pragma once
#include <map>
#include "Macro.h"
#include "..\..\Common\CatchMindPacket.h"
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
	int userIndex;

	NetworkManager();
	bool ProcessPacket(PACKET_INFO* packet, char * buf, DWORD & len);

public:
	~NetworkManager();
	void Init();
	void ProcessReceive(PACKET_INFO* packet, char * buf, DWORD & len);
	void AddUser(SOCKET clientSocket);
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

