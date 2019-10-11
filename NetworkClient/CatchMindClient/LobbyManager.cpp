#include <sstream>
#include "..\..\Common\NetworkManager.h"
#include "LobbyManager.h"
#include "BitMapManager.h"
#include "ChattingManager.h"
#include "CatchMind.h"

LobbyManager* LobbyManager::instance = nullptr;

LobbyManager::LobbyManager()
{
}

void LobbyManager::DrawBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_BACK)->Draw(hdc, 0, 0, 2, 2);
}

void LobbyManager::CreateRoom(string roomName, int inPlayerNum)
{
	Room* newRoom = new Room();
	newRoom->Init(roomCount, roomName, (roomCount % 2) * ROOM_WIDTH + ROOM_MARGINE_WIDTH, (roomCount / 2) * ROOM_HEIGHT + ROOM_MARGINE_HEIGHT, inPlayerNum, MAX_ROOM_IN_NUM);
	rooms.insert(make_pair(roomCount++, newRoom));
}

void LobbyManager::DrawRooms(HDC hdc)
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		iter->second->Render(hdc);
	}
}

void LobbyManager::DrawRoomCreateButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->Draw(hdc, 24, 24);
}

void LobbyManager::CheckIsClickedRoomCB(int x, int y)
{
	if (isCreateRoom || roomNum >= maxRoomNum)
		return;

	stringstream ss;
	ss << CatchMind::GetInstance()->playerIndex;
	string s = ss.str();
	if (x > 24 && x < 24 + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->GetSize().cx
		&& y > 24 && y < 24 + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->GetSize().cy)
	{
		isCreateRoom = true;
		string roomName = "플레이어" + s + "님의 방";
		CreateRoom(roomName);
		NetworkManager::GetInstance()->SendCreateRoom(roomName, CatchMind::GetInstance()->playerIndex);
		CatchMind::GetInstance()->SetSeceneState(SCENE_STATE::READY_SCENE);
	}
}

void LobbyManager::CheckIsClickedRoom(int x, int y)
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		if (iter->second->CheckIsClicked(x, y))
		{
			NetworkManager::GetInstance()->SendEnterRoom(iter->first, CatchMind::GetInstance()->playerIndex);
			CatchMind::GetInstance()->SetSeceneState(SCENE_STATE::READY_SCENE);
			CatchMind::GetInstance()->curTurn = CatchMind::GetInstance()->playerIndex;
		}
	}
}

void LobbyManager::ClearRooms()
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		SAFE_DELETE(iter->second);
	}
	rooms.clear();
}

void LobbyManager::UpdateRooms()
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		iter->second->Update();
	}
}

void LobbyManager::SetInPlayer(int roomNum, int* inPlayer)
{
	for (int i = 0; i < MAX_ROOM_IN_NUM; i++)
	{
		rooms[roomNum]->inPlayer[i] = inPlayer[i];
	}
}

void LobbyManager::SetIsStart(int roomNum, bool isStart)
{
	rooms[roomNum]->isStart = isStart;
}

int LobbyManager::GetRoomNum(int playerIndex)
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		for (int i = 0; i < MAX_ROOM_IN_NUM; i++)
		{
			if (iter->second->inPlayer[i] == playerIndex)
			{
				return iter->first;
			}
		}
	}
	return -1;
}

bool LobbyManager::CheckIsRoomMaster(int playerIndex)
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		if (iter->second->inPlayer[0] == playerIndex)
		{
			return true;
		}
	}
	return false;
}

bool LobbyManager::GetIsStart(int roomNum)
{
	return rooms[roomNum]->isStart;
}

bool LobbyManager::GetCanStart(int roomNum)
{
	return rooms[roomNum]->canStart;
}

void LobbyManager::SetCanStart(int roomNum, bool canStart)
{
	rooms[roomNum]->canStart = canStart;
}

LobbyManager::~LobbyManager()
{
}

void LobbyManager::Init(HWND hWnd, HINSTANCE g_hInst)
{
	roomNum = 0;
	roomCount = 0;
	maxRoomNum = 0;
	isCreateRoom = false;
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
	ChattingManager::GetInstance()->DrawChat(hdc);
	CatchMind::GetInstance()->DrawDockBar(hdc);
	CatchMind::GetInstance()->DrawBackButton(hdc);
	CatchMind::GetInstance()->DrawExitButton(hdc);
}

void LobbyManager::Release()
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		SAFE_DELETE(iter->second);
	}
	rooms.clear();
}
