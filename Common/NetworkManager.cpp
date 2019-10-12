#include "NetworkManager.h"
//#include <process.h>
//#include <WinSock2.h>

NetworkManager* NetworkManager::instance = nullptr;

NetworkManager::NetworkManager()
{
}

SOCKET NetworkManager::GetPlayerSocket(int playerIndex)
{
	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		if (iter->second->index == playerIndex)
		{
			return iter->first;
		}
	}
}

int NetworkManager::GetRoomNum(int playerIndex)
{
	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		if (iter->second->index == playerIndex)
		{
			return iter->second->inRoomNum;
		}
	}
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::Init()
{
	userIndex = 0;
	roomNum = 0;
	roomCount = 0;
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
	//send(clientSocket, (const char*)&packetBuf, packetBuf.header.len, 0);
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
	//WSASend(clientSocket, (LPWSABUF)&packetBuf, 1, (LPDWORD)packetBuf.header.len, 0, NULL, NULL);
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

void NetworkManager::SendDrawToServer(int roomNum, BRUSH_DATA& brushData)
{
	PACKET_DRAW_TO_SERVER packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_DRAW_TO_SERVER;
	packet.header.len = sizeof(packet);
	packet.roomNum = roomNum;
	packet.brushData.pos = brushData.pos;
	packet.brushData.color = brushData.color;
	packet.brushData.thickness = brushData.thickness;
	packet.brushData.isClickUp = brushData.isClickUp;
	send(clientSocket, (const char*)&packet, packet.header.len, 0);
}

void NetworkManager::SendDrawToClient(int roomNum)
{
	PACKET_DRAW_TO_CLIENT packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_DRAW_TO_CLIENT;
	packet.header.len = sizeof(packet);
	packet.brushData.pos = createdRooms[roomNum]->mouseTrack.back()->pos;
	packet.brushData.color = createdRooms[roomNum]->mouseTrack.back()->color;
	packet.brushData.thickness = createdRooms[roomNum]->mouseTrack.back()->thickness;
	packet.brushData.isClickUp = createdRooms[roomNum]->mouseTrack.back()->isClickUp;

	for (int i = 0; i < MAX_ROOM_IN_NUM; i++)
	{
		if (createdRooms[roomNum]->inPlayers[i] != -1)
		{
			send(GetPlayerSocket(createdRooms[roomNum]->inPlayers[i]), (const char*)&packet, packet.header.len, 0);
		}
		else
		{
			break;
		}
	}
}

void NetworkManager::SendSketchBookToEnterUser(int roomNum, int playerIndex)
{
	PACKET_SKETCH_BOOK packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_SKETCH_BOOK;
	packet.header.len = sizeof(PACKET_HEADER) + sizeof(int) + sizeof(BRUSH_DATA) * createdRooms[roomNum]->mouseTrack.size();
	packet.mouseTrackLen = createdRooms[roomNum]->mouseTrack.size();

	for (int i = 0; i < createdRooms[roomNum]->mouseTrack.size(); i++)
	{
		packet.mouseTrack[i].pos = createdRooms[roomNum]->mouseTrack[i]->pos;
		packet.mouseTrack[i].color = createdRooms[roomNum]->mouseTrack[i]->color;
		packet.mouseTrack[i].thickness = createdRooms[roomNum]->mouseTrack[i]->thickness;
		packet.mouseTrack[i].isClickUp = createdRooms[roomNum]->mouseTrack[i]->isClickUp;
	}

	send(GetPlayerSocket(playerIndex), (const char*)&packet, packet.header.len, 0);
}

void NetworkManager::BroadCastLobbyData()
{
	PACKET_LOBBY_DATA lobbyDataPacket;
	lobbyDataPacket.header.type = PACKET_TYPE::PACKET_TYPE_LOBBY_DATA;
	int i = 0;
	for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++, i++)
	{
		strcpy(lobbyDataPacket.lobyData.roomsData[i].roomName, iter->second->roomName);
		lobbyDataPacket.lobyData.roomsData[i].roomNum = iter->first;
		lobbyDataPacket.lobyData.roomsData[i].inPlayerNum = iter->second->inPlayerNum;
		lobbyDataPacket.lobyData.roomsData[i].isStart = iter->second->isStart;
		lobbyDataPacket.lobyData.roomsData[i].canStart = iter->second->canStart;
		for (int j = 0; j < MAX_ROOM_IN_NUM; j++)
		{
			lobbyDataPacket.lobyData.roomsData[i].inPlayer[j] = iter->second->inPlayers[j];
		}
	}
	lobbyDataPacket.lobyData.roomCount = roomCount;
	lobbyDataPacket.lobyData.maxRoomNum = MAX_ROOM_NUM;
	lobbyDataPacket.header.len = sizeof(PACKET_HEADER) + sizeof(int) + sizeof(int) + roomCount * sizeof(ROOM_DATA);

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
	if (roomCount >= MAX_ROOM_NUM)
		return false;

	ROOM_INFO* roomInfo = new ROOM_INFO();
	strcpy(roomInfo->roomName, packet.roomData.roomName);
	roomInfo->inPlayerNum = packet.roomData.inPlayerNum;
	roomInfo->inPlayers[0] = packet.roomData.inPlayer[0];
	//roomInfo->mouseTrack.reserve(1000);
	createdRooms.insert(make_pair(roomNum, roomInfo));

	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		if (iter->second->index == packet.roomData.inPlayer[0])
		{
			iter->second->inRoomNum = roomNum;
		}
	}
	roomNum++;
	roomCount++;

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
	if (roomNum == -1)
		return;

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

	if (createdRooms[roomNum]->inPlayerNum < 1)
	{
		for (auto iter = createdRooms[roomNum]->mouseTrack.begin(); iter != createdRooms[roomNum]->mouseTrack.end(); iter++)
		{
			SAFE_DELETE(*iter);
		}
		createdRooms[roomNum]->mouseTrack.clear();
		createdRooms.erase(roomNum);
		this->roomCount--;
	}
}

void NetworkManager::EndUser(SOCKET clientSocket)
{
	if (connectedUsers[clientSocket]->inRoomNum != -1)
	{
		int roomNum = connectedUsers[clientSocket]->inRoomNum;
		if (createdRooms[roomNum]->inPlayerNum == 1)
		{
			for (auto iter = createdRooms[roomNum]->mouseTrack.begin(); iter != createdRooms[roomNum]->mouseTrack.end(); iter++)
			{
				SAFE_DELETE(*iter);
			}
			createdRooms[roomNum]->mouseTrack.clear();
			createdRooms.erase(roomNum);
			this->roomCount--;
		}
		else
		{
			createdRooms[roomNum]->inPlayerNum--;
		}
	}

	SAFE_DELETE(connectedUsers[clientSocket]);
	connectedUsers.erase(clientSocket);
}

void NetworkManager::DrawToSketchBook(int roomNum, BRUSH_DATA brushData)
{
	BRUSH_DATA* newBrush = new BRUSH_DATA;
	newBrush->pos = brushData.pos;
	newBrush->color = brushData.color;
	newBrush->thickness = brushData.thickness;
	newBrush->isClickUp = brushData.isClickUp;
	createdRooms[roomNum]->mouseTrack.push_back(newBrush);
}

PACKET_INFO * NetworkManager::GetUserPacket(SOCKET clientSocket)
{
	return &connectedUsers[clientSocket]->userPacket;
}
