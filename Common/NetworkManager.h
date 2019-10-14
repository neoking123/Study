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
	int kungyaNum;
	char nickName[128];
	int inRoomNum = -1;
};

class ROOM_INFO
{
public:
	char roomName[128];
	int inPlayerNum;
	int roomMasyerNum;
	int inPlayers[MAX_ROOM_IN_NUM] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	bool readyState[MAX_ROOM_IN_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int curTurn = -1;
	char answer[32];
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
	void SendCreateRoom(string roomName, int playerIndex, int roomMasterNum);
	void SendEnterRoom(int roomNum, int playerIndex);
	void SendRoomState(int roomNum, int playerIndex, bool isReady, bool isStart = false);
	void SendBackToLobby(int roomNum, int playerIndex);
	void SendLoginToClient(SOCKET clientSocket);
	void SendLoginToServer(int playerIndex, char* nickName, int koungyaNum);
	void SendChat(int playerIndex, int roomNum, char* chat);
	void SendDrawToServer(int roomNum, BRUSH_DATA& brushData);
	void SendDrawToClient(int roomNum);
	void SendSketchBook(int roomNum, int playerIndex);
	void SendSketchBook(int roomNum);
	void SendChatToRoom(PACKET_CHAT& packet);
	void SendEraseAllToServer(int roomNum);
	void SendAnswerPlayer(int roomNum, int playerIndex, char* answerWord);
	void SetAnswerWordInServer(int roomNum, char* answerWord);
	void BroadCastLobbyData();
	void BroadCastPlayerData();
	bool CreateRoom(PACKET_CREATE_ROOM packet);
	void EnterRoom(int roomNum, int playerIndex);
	void BackToLobby(int roomNum, int playerIndex);
	void EndUser(SOCKET clientSocket);
	void DrawToSketchBook(int roomNum, BRUSH_DATA brushData);
	void SetNickName(int playerIndex, char* nickName);
	void SetKungyaNum(int playerIndex, int kungyaNum);
	void EraseAllSketchBook(int roomNum);
	void SetRoomState(int roomNum, int playerIndex, bool isReady, bool isStart);
	bool CheckIsStart(int roomNum);
	bool CheckIsAnswer(int roomNum, char* answerWord);
	void SetNextTurn(int roomNum);
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
		SAFE_DELETE(instance);
	}
};

