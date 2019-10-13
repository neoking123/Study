#include <sstream>
#include "..\..\Common\NetworkManager.h"
#include "LobbyManager.h"
#include "BitMapManager.h"
#include "ChattingManager.h"
#include "CatchMind.h"

LobbyManager* LobbyManager::instance = nullptr;
std::mutex LobbyManager::mutex;

LobbyManager::LobbyManager()
{
}

void LobbyManager::DrawBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_BACK)->Draw(hdc, 0, 0, 2, 2);
}

void LobbyManager::CreateRoom(int roomNum, string roomName, int inPlayerNum)
{
	Room* newRoom = new Room();
	newRoom->Init(roomNum, roomAlignCount, roomName, (roomAlignCount % 2) * ROOM_WIDTH + ROOM_MARGINE_WIDTH, (roomAlignCount / 2) * ROOM_HEIGHT + ROOM_MARGINE_HEIGHT, inPlayerNum, MAX_ROOM_IN_NUM);
	rooms.insert(make_pair(roomNum, newRoom));
	roomAlignCount++;
	mutex.unlock();

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
	{
		return;
	}

	stringstream ss;
	ss << CatchMind::GetInstance()->playerIndex;
	string s = ss.str();
	if (x > 24 && x < 24 + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->GetSize().cx
		&& y > 24 && y < 24 + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->GetSize().cy)
	{
		isCreateRoom = true;
		string roomName = "플레이어" + s + "님의 방";
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
	mutex.unlock();
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

	mutex.unlock();
}

void LobbyManager::SetIsStart(int roomNum, bool isStart)
{
	rooms[roomNum]->isStart = isStart;
	mutex.unlock();
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
	mutex.unlock();
}

void LobbyManager::SetPlayers(int playterIndex, char * nickName)
{
	Player* player = new Player;
	strcpy(player->nickName, nickName);
	players.insert(make_pair(playterIndex, player));
	mutex.unlock();
}

void LobbyManager::ClearPlayers()
{
	for (auto iter = players.begin(); iter != players.end(); iter++)
	{
		SAFE_DELETE(iter->second);
	}
	players.clear();
	mutex.unlock();
}

LobbyManager::~LobbyManager()
{
}

void LobbyManager::Init(HWND hWnd, HINSTANCE g_hInst)
{
	roomNum = 0;
	roomCount = 0;
	maxRoomNum = 0;
	roomAlignCount = 0;
	playerCount = 0;
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

	mutex.unlock();
}

void LobbyManager::Release()
{
	for (auto iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		SAFE_DELETE(iter->second);
	}
	rooms.clear();

}
