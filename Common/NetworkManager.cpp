#include "NetworkManager.h"
#include <process.h>

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

void NetworkManager::ProcessClientReceive(PACKET_INFO* packet, char * buf, int & len)
{
	// 바이트 스트림 처리
	while (true)
	{
		if (!ProcessClientPacket(packet, buf, len))
		{
			Sleep(100);
			break;
		}
		else
		{
			if (packet->len < sizeof(PACKET_HEADER))
				break;
		}
	}
}

void NetworkManager::ProcessServerReceive(PACKET_INFO * packet, char * buf, int & len)
{
	// 바이트 스트림 처리
	while (true)
	{
		if (!ProcessServerPacket(packet, buf, len))
		{
			Sleep(100);
			break;
		}
		else
		{
			if (packet->len < sizeof(PACKET_HEADER))
				break;
		}
	}
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
	send(clientSocket, (const char*)&packet, packet.header.len, 0);
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
}

PACKET_INFO * NetworkManager::GetUserPacket(SOCKET clientSocket)
{
	return &connectedUsers[clientSocket]->userPacket;
}

bool NetworkManager::ProcessClientPacket(PACKET_INFO* packet, char * buf, int & len)
{
	if (len > 0)
	{
		memcpy(&packet->buf[packet->len], buf, len);
		packet->len += len;
		len = 0;
	}

	if (packet->len < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, packet->buf, sizeof(header));

	switch (header.type)
	{
	case PACKET_TYPE::PACKET_TYPE_LOGIN:
	{
		PACKET_LOGIN packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_USER_DATA:
	{
		PACKET_USER_DATA packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_LOBBY_DATA:
	{
		PACKET_LOBBY_DATA packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_MOVE_TO:
	{
		PACKET_MOVE_TO packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_CHAT:
	{
		PACKET_CHAT packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	}

	memcpy(&packet->buf, &packet->buf[header.len], packet->len - header.len);
	packet->len -= header.len;

	return true;
}

bool NetworkManager::ProcessServerPacket(PACKET_INFO * packet, char * buf, int & len)
{
	if (len > 0)
	{
		memcpy(&packet->buf[packet->len], buf, len);
		packet->len += len;
		len = 0;
	}

	if (packet->len < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, packet->buf, sizeof(header));

	switch (header.type)
	{
	case PACKET_TYPE::PACKET_TYPE_LOGIN:
	{
		PACKET_LOGIN packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_USER_DATA:
	{
		PACKET_USER_DATA packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_LOBBY_DATA:
	{
		PACKET_LOBBY_DATA packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_MOVE_TO:
	{
		PACKET_MOVE_TO packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_CHAT:
	{
		PACKET_CHAT packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	}

	memcpy(&packet->buf, &packet->buf[header.len], packet->len - header.len);
	packet->len -= header.len;

	return true;
}
