#include <sstream>
#include "LobbyManager.h"
#include "BitMapManager.h"
#include "Room.h"
#include "Macro.h"
#include "..\..\Common\ChessPacket.h"
#include "ChessGame.h"

LobbyManager* LobbyManager::instance = nullptr;

LobbyManager::LobbyManager()
{
}

void LobbyManager::DrawBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_BACK)->Draw(hdc, 0, 0, 2, 2);
}

void LobbyManager::CreateRoom(string roomName)
{
	Room* newRoom = new Room();
	newRoom->Init(roomCount, roomName, (roomCount % 2) * ROOM_WIDTH + ROOM_MARGINE_WIDTH, (roomCount / 2) * ROOM_HEIGHT + ROOM_MARGINE_HEIGHT, 2);
	rooms.insert(make_pair(roomCount++, newRoom));
}

void LobbyManager::DrawRooms(HDC hdc)
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		(*iter).second->Render(hdc);
	}
}

void LobbyManager::DrawRoomCreateButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->Draw(hdc, 24, 24);
}

void LobbyManager::CheckIsClickedRoomCB(int x, int y)
{
	stringstream ss;
	ss << ChessGame::GetInstance()->playerIndex;
	string s = ss.str();
	if (x > 24 && x < 24 + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->GetSize().cx
		&& y > 24 && y < 24 + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->GetSize().cy)
	{
		string roomName = s + "님의 방";
		CreateRoom(roomName);
		SendCreateRoom(roomName);
	}
}

void LobbyManager::CheckIsClickedRoom(int x, int y)
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		if ((*iter).second->CheckIsClicked(x, y))
		{
			// 방 클릭
		}
	}
}

void LobbyManager::ClearRooms()
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		SAFE_DELETE((*iter).second);
	}
	rooms.clear();
}

void LobbyManager::UpdateRooms()
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		(*iter).second->Update();
	}
}

void LobbyManager::SendCreateRoom(string roomName)
{
	PACKET_CREATE_ROOM packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_CREATE_ROOM;
	packet.header.len = sizeof(packet);
	strcpy(packet.roomData.roomName, roomName.c_str());

	send(sock, (const char*)&packet, sizeof(packet), 0);
}

LobbyManager::~LobbyManager()
{
}

void LobbyManager::Init(SOCKET sock)
{
	this->sock = sock;
	roomNum = 0;
	roomCount = 0;
}

void LobbyManager::Update()
{
	UpdateRooms();
}

void LobbyManager::Render(HDC hdc)
{
	DrawBackground(hdc);
	DrawRooms(hdc);
	DrawRoomCreateButton(hdc);
}

void LobbyManager::Release()
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		SAFE_DELETE((*iter).second);
	}
	rooms.clear();
}
