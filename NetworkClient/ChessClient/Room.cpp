#include "Room.h"
#include "BitMapManager.h"

void Room::DrawRoomFrame(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_FRAME)->Draw(hdc, transform.position.x, transform.position.y);
}

void Room::DrawRoomName(HDC hdc)
{
	TCHAR roomName[128];
	HFONT myFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(5, 148, 224));

	wsprintf(roomName, TEXT("%s"), this->roomName.c_str());
	TextOut(hdc, transform.position.x + 140, transform.position.y + 17, roomName, lstrlen(roomName));

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void Room::DrawRoomNumber(HDC hdc)
{
	TCHAR roomNumber[128];
	HFONT myFont = CreateFont(14, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 172, 252));

	wsprintf(roomNumber, TEXT("%d"), roomNum);
	TextOut(hdc, transform.position.x + 88, transform.position.y + 19, roomNumber, lstrlen(roomNumber));

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void Room::DrawRoomIcon(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_ICON_0)->Draw(hdc, transform.position.x + 8, transform.position.y + 8);
}

void Room::DrawInPlayerNum(HDC hdc)
{
	TCHAR inPlayer[128];
	HFONT myFont = CreateFont(14, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(30, 170, 239));

	wsprintf(inPlayer, TEXT("%d / %d"), inPlayerNum, MaxInPlayerNum);
	TextOut(hdc, transform.position.x + 214, transform.position.y + 51, inPlayer, lstrlen(inPlayer));

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void Room::DrawRoomState(HDC hdc)
{
	switch (roomState)
	{
	case ROOM_STATE::ROOM_WATING:
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_WAITING)->Draw(hdc, transform.position.x + 84, transform.position.y + 46);
		break;
	case ROOM_STATE::ROOM_FULL:
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_FULL)->Draw(hdc, transform.position.x + 84, transform.position.y + 46);
		break;
	case ROOM_STATE::ROOM_PLAYING:
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_PLAYING)->Draw(hdc, transform.position.x + 84, transform.position.y + 46);
		break;
	}
}

void Room::DarwPlayerIcon(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_PLAYER_ICON)->Draw(hdc, transform.position.x + 239, transform.position.y + 45);
}

void Room::DrawKeyIcon(HDC hdc)
{
	if (!isSecret)
		return;
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_KEY_ICON)->Draw(hdc, transform.position.x + 190, transform.position.y + 45);
}

bool Room::CheckIsClicked(int x, int y)
{
	bool isClicked = false;
	if (button.CheckIsCliked(*this, x, y))
	{
		if (inPlayerNum < MaxInPlayerNum)
		{
			//roomName = "Enter Room!";
			inPlayerNum++;
			isClicked = true;
		}
	}

	return isClicked;
}

void Room::CheckRoomState()
{
	if (isStart)
	{
		roomState = ROOM_STATE::ROOM_PLAYING;
	}
	else if (inPlayerNum < MaxInPlayerNum)
	{
		roomState = ROOM_STATE::ROOM_WATING;
	}
	else
	{
		roomState = ROOM_STATE::ROOM_FULL;
	}
}

Room::Room()
{
}

Room::~Room()
{
}

void Room::Init(int roomNum, string roomName, int x, int y, int MaxInPlayerNum, bool isSecret, string password)
{
	tag = "room";
	this->roomNum = roomNum;
	this->roomName = roomName;
	transform.position.x = x;
	transform.position.y = y;
	roomState = ROOM_STATE::ROOM_WATING;
	
	inPlayerNum = 0;
	this->MaxInPlayerNum = MaxInPlayerNum;
	this->isSecret = isSecret;
	this->password = password;
	isStart = false;
}

void Room::Update()
{
	CheckRoomState();
}

void Room::Init(int x, int y)
{
}

void Room::Render(HDC hdc)
{
	DrawRoomFrame(hdc);
	DrawRoomIcon(hdc);
	DrawRoomName(hdc);
	DrawRoomNumber(hdc);
	DrawInPlayerNum(hdc);
	DrawRoomState(hdc);
	DarwPlayerIcon(hdc);
	DrawKeyIcon(hdc);
}

void Room::Release()
{

}
