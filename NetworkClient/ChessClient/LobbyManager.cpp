#include <sstream>
#include "LobbyManager.h"
#include "BitMapManager.h"
#include "Room.h"
#include "Macro.h"


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
	newRoom->Init(roomNum, roomName, (roomNum % 2) * ROOM_WIDTH + ROOM_MARGINE_WIDTH, (roomNum / 2) * ROOM_HEIGHT + ROOM_MARGINE_HEIGHT, 2);
	rooms.push_back(newRoom);
	roomNum++;
}

void LobbyManager::DrawRooms(HDC hdc)
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		(*iter)->Render(hdc);
	}
}

void LobbyManager::DrawRoomCreateButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->Draw(hdc, 24, 24);
}

void LobbyManager::CheckIsClickedRoomCB(int x, int y)
{
	stringstream ss;
	ss << roomNum;
	string s = ss.str();
	if (x > 24 && x < 24 + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->GetSize().cx
		&& y > 24 && y < 24 + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->GetSize().cy)
	{
		CreateRoom("Å×½ºÆ® ·ë" + s);
	}
}

void LobbyManager::CheckIsClickedRoom(int x, int y)
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		(*iter)->CheckIsCliked(x, y);
	}
}

void LobbyManager::UpdateRooms()
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		(*iter)->Update();
	}
}

LobbyManager::~LobbyManager()
{
}

void LobbyManager::Init()
{
	roomNum = 0;
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
		SAFE_DELETE(*iter);
	}
}
