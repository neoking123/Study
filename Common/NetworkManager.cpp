#include "NetworkManager.h"
//#include <process.h>
//#include <WinSock2.h>

NetworkManager* NetworkManager::instance = nullptr;

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::Init()
{
	userIndex = 0;
	roomNum = 0;
}

void NetworkManager::Release()
{
	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		SAFE_DELETE(iter->second);
	}
}

void NetworkManager::SetClientSocket(SOCKET clientSocket)
{
	this->clientSocket = clientSocket;
}

void NetworkManager::AddUser(SOCKET clientSocket)
{
	USER_INFO* playerInfo = new USER_INFO();
	playerInfo->index = userIndex++;
	playerInfo->userPacket.len = 0;
	connectedUsers.insert(make_pair(clientSocket, playerInfo));
}

void NetworkManager::SendCreateRoom(string roomName, int playerIndex)
{
	PACKET_CREATE_ROOM packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_CREATE_ROOM;
	packet.header.len = sizeof(packet);
	strcpy(packet.roomData.roomName, roomName.c_str());
	packet.roomData.inPlayerNum = 1;
	packet.roomData.inPlayer[0] = playerIndex;
	packet.roomData.isStart = false;
	packet.roomData.canStart = false;
	send(clientSocket, (const char*)&packet, packet.header.len, 0);
}

void NetworkManager::SendEnterRoom(int roomNum, int playerIndex)
{
	PACKET_ENTER_ROOM packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_ENTER_ROOM;
	packet.header.len = sizeof(packet);
	packet.playerIndex = playerIndex;
	packet.roomNum = roomNum;
	send(clientSocket, (const char*)&packet, packet.header.len, 0);
}

void NetworkManager::SendRoomState(int roomNum, bool isStart, bool canStart)
{
	PACKET_ROOM_STATE packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_ROOM_STATE;
	packet.header.len = sizeof(packet);
	packet.isStart = isStart;
	packet.canStart = canStart;
	packet.roomNum = roomNum;
	//send(clientSocket, (const char*)&packet, packet.header.len, 0);
}

void NetworkManager::SendBackToLobby(int playerIndex, int roomNum)
{
	PACKET_BACK_TO_LOBBY packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_BACK_TO_LOBBY;
	packet.header.len = sizeof(packet);
	packet.playerIndex = playerIndex;
	packet.roomNum = roomNum;
	send(clientSocket, (const char*)&packet, packet.header.len, 0);
}

void NetworkManager::SendLogin(SOCKET clientSocket)
{
	// 로그인 정보 전송
	PACKET_LOGIN packet;
	packet.header.type = PACKET_TYPE_LOGIN;
	packet.header.len = sizeof(PACKET_LOGIN);
	packet.loginIndex = connectedUsers[clientSocket]->index;
	send(clientSocket, (const char*)&packet, packet.header.len, 0);
	//WSASend(clientSocket, (LPWSABUF)&packet, 1, (LPDWORD)packet.header.len, 0, NULL, NULL);
}

void NetworkManager::SendChat(int playerIndex, int roomNum, char* chat)
{
	PACKET_CHAT packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_CHAT;
	packet.header.len = sizeof(packet);
	packet.playerIndex = playerIndex;
	packet.roomNum = roomNum;
	strcpy(packet.chat, chat);
	send(clientSocket, (const char*)&packet, packet.header.len, 0);
}

void NetworkManager::BroadCastLobbyData()
{
	PACKET_LOBBY_DATA lobbyDataPacket;
	lobbyDataPacket.header.type = PACKET_TYPE::PACKET_TYPE_LOBBY_DATA;
	int i = 0;
	for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++, i++)
	{
		strcpy(lobbyDataPacket.lobyData.roomsData[i].roomName, createdRooms[i]->roomName);
		lobbyDataPacket.lobyData.roomsData[i].inPlayerNum = createdRooms[i]->inPlayerNum;
		lobbyDataPacket.lobyData.roomsData[i].isStart = createdRooms[i]->isStart;
		lobbyDataPacket.lobyData.roomsData[i].canStart = createdRooms[i]->canStart;
		for (int j = 0; j < MAX_ROOM_IN_NUM; j++)
		{
			lobbyDataPacket.lobyData.roomsData[i].inPlayer[j] = createdRooms[i]->inPlayers[j];
		}
	}
	lobbyDataPacket.lobyData.roomNum = roomNum;
	lobbyDataPacket.lobyData.maxRoomNum = MAX_ROOM_NUM;
	lobbyDataPacket.header.len = sizeof(PACKET_HEADER) + sizeof(int) + sizeof(int) + roomNum * sizeof(ROOM_DATA);

	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		send(iter->first, (const char*)&lobbyDataPacket, lobbyDataPacket.header.len, 0);
		//WSASend(iter->first, (LPWSABUF)&lobbyDataPacket, 1, (LPDWORD)lobbyDataPacket.header.len, 0, NULL, NULL);
	}
}

void NetworkManager::SendChatToRoom(PACKET_CHAT& packet)
{
	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		if (iter->second->inRoomNum == packet.roomNum)
		{
			send(iter->first, (const char*)&packet, packet.header.len, 0);
		}
	}
}

bool NetworkManager::CreateRoom(PACKET_CREATE_ROOM packet)
{
	if (roomNum >= MAX_ROOM_NUM)
		return false;

	ROOM_INFO* roomInfo = new ROOM_INFO();
	strcpy(roomInfo->roomName, packet.roomData.roomName);
	roomInfo->inPlayerNum = packet.roomData.inPlayerNum;
	roomInfo->inPlayers[0] = packet.roomData.inPlayer[0];
	//InitChessBoard(roomInfo->board);
	//InitSpectatorArray(roomInfo->spectators);
	createdRooms.insert(make_pair(roomNum, roomInfo));

	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		if (iter->second->index == packet.roomData.inPlayer[0])
		{
			iter->second->inRoomNum = roomNum;
		}
	}
	roomNum++;

	return true;
}

void NetworkManager::EnterRoom(int roomNum, int playerIndex)
{
	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		if (iter->second->index == playerIndex)
		{
			iter->second->inRoomNum = roomNum;
		}
	}

	for (int i = 0; i < MAX_ROOM_IN_NUM; i++)
	{
		if (createdRooms[roomNum]->inPlayers[i] == -1)
		{
			createdRooms[roomNum]->inPlayers[i] = playerIndex;
			break;
		}
	}

	createdRooms[roomNum]->inPlayerNum++;	
}

void NetworkManager::BackToLobby(int roomNum, int playerIndex)
{
	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		if (iter->second->index == playerIndex)
		{
			iter->second->inRoomNum = -1;
		}
	}

	for (int i = 0; i < MAX_ROOM_IN_NUM; i++)
	{
		if (createdRooms[roomNum]->inPlayers[i] == playerIndex)
		{
			createdRooms[roomNum]->inPlayers[i] = -1;
			break;
		}
	}

	createdRooms[roomNum]->inPlayerNum--;

	if (createdRooms[roomNum]->inPlayerNum <= 0)
	{
		createdRooms.erase(roomNum);
		this->roomNum--;
	}
}

void NetworkManager::EndUser(SOCKET clientSocket)
{
	SAFE_DELETE(connectedUsers[clientSocket]);
	connectedUsers.erase(clientSocket);
}

PACKET_INFO * NetworkManager::GetUserPacket(SOCKET clientSocket)
{
	return &connectedUsers[clientSocket]->userPacket;
}
