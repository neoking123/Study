#include "NetworkManager.h"

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

void NetworkManager::ProcessReceive(PACKET_INFO* packet, char * buf, DWORD & len)
{
	// 바이트 스트림 처리
	while (true)
	{
		if (!ProcessPacket(packet, buf, len))
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

PACKET_INFO * NetworkManager::GetUserPacket(SOCKET clientSocket)
{
	return &connectedUsers[clientSocket]->userPacket;
}

bool NetworkManager::ProcessPacket(PACKET_INFO* packet, char * buf, DWORD & len)
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