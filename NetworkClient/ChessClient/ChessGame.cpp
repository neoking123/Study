#include "ChessGame.h"
#include "BitMapManager.h"
#include "LobbyManager.h"
#include "..\..\Common\ChessPacket.h"
#include "Macro.h"
#include "ChessBoard.h"

ChessGame* ChessGame::instance = nullptr;

ChessGame::ChessGame()
{
}

void ChessGame::DrawInRoom(HDC hdc)
{
	DrawBackground(hdc);
	//DrawChessBoard(hdc);
	DrawInfoBackground(hdc);
	DrawInPlayerInfo(hdc);
	DrawRoomNum(hdc);
	DrawButton(hdc);
	DrawRoomState_Debug(hdc);
}

void ChessGame::DrawBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_BACK)->Draw(hdc, 0, 0, 2, 2);
}

void ChessGame::DrawChessBoard(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::CHESS_BOARD)->Draw(hdc, 24, 24);
}

void ChessGame::DrawChessPieces(HDC hdc)
{
	
}

void ChessGame::DrawInfoBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_ROOM_INFO_BACK)->Draw(hdc, 800, 24);
}

void ChessGame::DrawInPlayerInfo(HDC hdc)
{
	int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
	int player0 = LobbyManager::GetInstance()->rooms[roomNum]->inPlayer[0];
	int player1 = LobbyManager::GetInstance()->rooms[roomNum]->inPlayer[1];

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_PLAYER_INFO)->Draw(hdc, 810, 75);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_PLAYER_INFO)->Draw(hdc, 810, 100);

	TCHAR inPlayer0[128];
	TCHAR inPlayer1[128];
	TCHAR roomMaster[128];
	HFONT myFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));

	SetBkColor(hdc, RGB(30, 123, 203));
	wsprintf(roomMaster, TEXT("☆"));
	TextOut(hdc, 819, 77, roomMaster, lstrlen(roomMaster));

	SetBkColor(hdc, RGB(0, 91, 184));

	wsprintf(inPlayer0, TEXT("플레이어%d"), player0);
	TextOut(hdc, 840, 78, inPlayer0, lstrlen(inPlayer0));

	if (player1 == -1)
	{
		wsprintf(inPlayer1, TEXT("대기중"));
		TextOut(hdc, 840, 103, inPlayer1, lstrlen(inPlayer1));
	}
	else
	{
		wsprintf(inPlayer1, TEXT("플레이어%d"), player1);
		TextOut(hdc, 840, 103, inPlayer1, lstrlen(inPlayer1));
	}
	

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void ChessGame::DrawRoomNum(HDC hdc)
{
	int rn = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
	TCHAR roomNum[128];
	HFONT myFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 122, 244));

	wsprintf(roomNum, TEXT("방 번호 : %d"), rn);
	TextOut(hdc, 820, 40, roomNum, lstrlen(roomNum));

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void ChessGame::DrawButton(HDC hdc)
{
	if (LobbyManager::GetInstance()->CheckIsRoomMaster(playerIndex))
	{
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_START)->Draw(hdc, START_BUTTON_POSITION_X, START_BUTTON_POSITION_Y);
	}
	else
	{
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_READY)->Draw(hdc, START_BUTTON_POSITION_X, START_BUTTON_POSITION_Y);
	}
	
}

bool ChessGame::CheckIsClickedStateButton(int x, int y)
{
	if (x > START_BUTTON_POSITION_X && x < START_BUTTON_POSITION_X + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_START)->GetSize().cx
		&& y > START_BUTTON_POSITION_Y && y < START_BUTTON_POSITION_Y + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_START)->GetSize().cy)
	{
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
		if (LobbyManager::GetInstance()->CheckIsRoomMaster(playerIndex))
		{
			if (LobbyManager::GetInstance()->GetCanStart(roomNum))
			{
				bool isStart = true;
				LobbyManager::GetInstance()->SetIsStart(roomNum, isStart);
				SendRoomState(roomNum, isStart);
			}
		}
		else
		{
			bool canStart;
			if (LobbyManager::GetInstance()->GetIsStart(roomNum))
				return true;

			if (LobbyManager::GetInstance()->GetCanStart(roomNum))
			{
				canStart = false;
				LobbyManager::GetInstance()->SetCanStart(roomNum, canStart);
				SendRoomState(roomNum, false, canStart);
			}
			else
			{
				canStart = true;
				LobbyManager::GetInstance()->SetCanStart(roomNum, canStart);
				SendRoomState(roomNum, false, canStart);
			}
		}
		return true;
	}
	return false;
}

void ChessGame::SendRoomState(int roomNum, bool isStart, bool canStart)
{
	PACKET_ROOM_STATE packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_ROOM_STATE;
	packet.header.len = sizeof(packet);
	packet.isStart = isStart;
	packet.canStart = canStart;
	packet.roomNum = roomNum;
	send(sock, (const char*)&packet, packet.header.len, 0);
}

void ChessGame::DrawRoomState_Debug(HDC hdc)
{
	int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
	bool isStart = LobbyManager::GetInstance()->GetIsStart(roomNum);
	bool canStart = LobbyManager::GetInstance()->GetCanStart(roomNum);

	TCHAR isStr[128];
	TCHAR canStr[128];
	HFONT myFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 122, 244));

	if (isStart)
	{
		wsprintf(isStr, TEXT("게임 시작 : YES"));
		TextOut(hdc, 820, 250, isStr, lstrlen(isStr));
	}
	else
	{
		wsprintf(isStr, TEXT("게임 시작 : NO"));
		TextOut(hdc, 820, 250, isStr, lstrlen(isStr));
	}
	
	if (canStart)
	{
		wsprintf(isStr, TEXT("게임 준비 : OK"));
		TextOut(hdc, 820, 270, isStr, lstrlen(isStr));
	}
	else
	{
		wsprintf(isStr, TEXT("게임 준비 : NO"));
		TextOut(hdc, 820, 270, isStr, lstrlen(isStr));
	}

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void ChessGame::CheckStart()
{
	int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
	if (LobbyManager::GetInstance()->GetIsStart(roomNum))
	{
		sceneState = SCENE_STATE::INGAME_SCENE;
	}
}

void ChessGame::DrawInGame(HDC hdc)
{
	DrawBackground(hdc);
	//DrawChessBoard(hdc);
	DrawInfoBackground(hdc);
	DrawInPlayerInfo(hdc);
	DrawRoomNum(hdc);
	DrawChessPieces(hdc);
}

void ChessGame::InGameInit()
{
	chessBoard = new ChessBoard();
	chessBoard->Init();
}

ChessGame::~ChessGame()
{
}

void ChessGame::Init(HWND hWnd, SOCKET sock)
{
	lastTime = std::chrono::system_clock::now();
	playerIndex = 0;
	this->hWnd = hWnd;
	this->sock = sock;
	HDC hdc = GetDC(hWnd);
	cursor = { 0, 0 };

	gameDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, INGAME_WIDTH, INGAME_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(gameDC, hBitmap);

	BitMapManager::GetInstance()->Init(gameDC);
	LobbyManager::GetInstance()->Init(sock);

	sceneState = SCENE_STATE::LOBY_SCENE;
	InGameInit();
	ReleaseDC(hWnd, hdc);
}

void ChessGame::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - lastTime;
	if (sec.count() < (1 / FPS))
		return;

	elapseTime = sec.count();

	switch (sceneState)
	{
	case SCENE_STATE::LOGIN_SCENE:
		break;

	case SCENE_STATE::LOBY_SCENE:
		LobbyManager::GetInstance()->Update();
		break;

	case SCENE_STATE::READY_SCENE:
		CheckStart();
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}

	Render();

	lastTime = std::chrono::system_clock::now();
}

void ChessGame::Render()
{
	HDC hdc = GetDC(hWnd);

	switch (sceneState)
	{
	case SCENE_STATE::LOGIN_SCENE:
		break;

	case SCENE_STATE::LOBY_SCENE:
		LobbyManager::GetInstance()->Render(gameDC);
		break;

	case SCENE_STATE::READY_SCENE:
		DrawInRoom(gameDC);
		chessBoard->Render(gameDC);
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		DrawInGame(gameDC);
		chessBoard->Render(gameDC);
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}

	BitBlt(hdc, 0, 0, INGAME_WIDTH, INGAME_HEIGHT, gameDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

void ChessGame::Release()
{
	chessBoard->Release();
	SAFE_DELETE(chessBoard);
	LobbyManager::GetInstance()->Release();
	BitMapManager::GetInstance()->Release();
}

void ChessGame::MouseInput(int x, int y, int mouseState)
{
	if (mouseState == MOUSE_STATE::CLICK_DOWN)
	{
		cursor = { x, y };
	}
	else if(mouseState == MOUSE_STATE::CLICK_UP)
	{
		cursor = { 0, 0 };
	}

	switch (sceneState)
	{
	case SCENE_STATE::LOGIN_SCENE:
		break;

	case SCENE_STATE::LOBY_SCENE:
		LobbyManager::GetInstance()->CheckIsClickedRoomCB(cursor.x, cursor.y);
		LobbyManager::GetInstance()->CheckIsClickedRoom(cursor.x, cursor.y);
		break;

	case SCENE_STATE::READY_SCENE:
		CheckIsClickedStateButton(cursor.x, cursor.y);
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		chessBoard->MouseInput(cursor.x, cursor.y);
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}
}
