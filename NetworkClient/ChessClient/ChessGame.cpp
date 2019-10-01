#include "ChessGame.h"
#include "BitMapManager.h"
#include "LobbyManager.h"
#include "ChattingManager.h"
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
	DrawDockBar(hdc);
	DrawInfoBackground(hdc);
	DrawInPlayerInfo(hdc);
	DrawRoomNum(hdc);
	DrawStartButton(hdc);
	DrawRoomState_Debug(hdc);
	DrawBackButton(hdc);
	DrawExitButton(hdc);
	ChattingManager::GetInstance()->DrawChat(hdc);
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

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_ROOM_PLAYER_COLOR_W)->Draw(hdc, 910, 77);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_ROOM_PLAYER_COLOR_B)->Draw(hdc, 910, 102);

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

void ChessGame::DrawStartButton(HDC hdc)
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

void ChessGame::DrawBackButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->Draw(hdc, BACK_BUTTON_POSITION_X, BACK_BUTTON_POSITION_Y);
}

void ChessGame::DrawExitButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::EXIT_ICON)->Draw(hdc, BACK_BUTTON_POSITION_X + 50, BACK_BUTTON_POSITION_Y);
}

void ChessGame::DrawDockBar(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::DOCK_BAR)->Draw(hdc, 0, DOCK_BAR_POSITION, 2, 1);
}

void ChessGame::DrawCurTurn(HDC hdc)
{
	TCHAR turn[128];
	HFONT myFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 122, 244));

	wsprintf(turn, TEXT("현재 턴 : "));
	TextOut(hdc, 820, 150, turn, lstrlen(turn));

	if (curTurn != playerIndex)
	{
		if (ChessBoard::GetInstance()->GetPlayerColor() == 0)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_ROOM_PLAYER_COLOR_B)->Draw(hdc, 880, 150);
		}
		else if (ChessBoard::GetInstance()->GetPlayerColor() == 1)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_ROOM_PLAYER_COLOR_W)->Draw(hdc, 880, 150);
		}
	}
	else
	{
		if (ChessBoard::GetInstance()->GetPlayerColor() == 0)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_ROOM_PLAYER_COLOR_W)->Draw(hdc, 880, 150);
		}
		else if (ChessBoard::GetInstance()->GetPlayerColor() == 1)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_ROOM_PLAYER_COLOR_B)->Draw(hdc, 880, 150);
		}
	}

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void ChessGame::DrawCheckState(HDC hdc)
{
	if (ChessBoard::GetInstance()->checkmate != -1)
	{
		TCHAR check[128];
		HFONT myFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 122, 244));

		wsprintf(check, TEXT("플레이어%d 승리!!"), ChessBoard::GetInstance()->checkmate);
		TextOut(hdc, 820, 180, check, lstrlen(check));

		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(255, 255, 255));
		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}
	else
	{
		if (!ChessBoard::GetInstance()->checkState)
			return;

		TCHAR check[128];
		HFONT myFont = CreateFont(20, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 122, 244));

		wsprintf(check, TEXT("""CHECK!!"""));
		TextOut(hdc, 830, 180, check, lstrlen(check));

		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(255, 255, 255));
		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}
}

void ChessGame::DrawChat(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBBY_CHAT)->Draw(hdc, 50, 700);
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

void ChessGame::CheckIsClickedBackButton(int x, int y)
{
	if (x > BACK_BUTTON_POSITION_X && x < BACK_BUTTON_POSITION_X + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->GetSize().cx
		&& y > BACK_BUTTON_POSITION_Y && y < BACK_BUTTON_POSITION_Y + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->GetSize().cy)
	{
		sceneState = SCENE_STATE::LOBY_SCENE;
		LobbyManager::GetInstance()->ActivateCreateRoom();
		ChessBoard::GetInstance()->CleanPieces();
		ChessBoard::GetInstance()->Init();
		curTurn = -1;
		SendBackToLobby();
	}
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

void ChessGame::SendBackToLobby()
{
	PACKET_BACK_TO_LOBBY packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_BACK_TO_LOBBY;
	packet.header.len = sizeof(packet);
	packet.playerIndex = playerIndex;
	packet.roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
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
		if (LobbyManager::GetInstance()->CheckIsRoomMaster(playerIndex))
		{
			curTurn = -1;
			ChessBoard::GetInstance()->SetPlayerColor(1);
		}
		else
		{
			curTurn = playerIndex;
			ChessBoard::GetInstance()->SetPlayerColor(0);
		}
		sceneState = SCENE_STATE::INGAME_SCENE;
	}
}

void ChessGame::DrawInGame(HDC hdc)
{
	DrawBackground(hdc);
	DrawDockBar(hdc);
	DrawInfoBackground(hdc);
	DrawInPlayerInfo(hdc);
	DrawCurTurn(hdc);
	DrawRoomNum(hdc);
	DrawChessPieces(hdc);
	DrawCheckState(hdc);
	DrawBackButton(hdc);
	DrawExitButton(hdc);
	ChattingManager::GetInstance()->DrawChat(hdc);
}

void ChessGame::InGameInit()
{
	ChessBoard::GetInstance()->Init();
}

void ChessGame::CheckCheckmate(float elapseTime)
{
	if (ChessBoard::GetInstance()->checkmate != -1)
	{
		if (reStartTime < 2.0f)
		{
			reStartTime += elapseTime;
			return;
		}
		reStartTime = 0.0f;

		ChessBoard::GetInstance()->CleanPieces();
		ChessBoard::GetInstance()->Init();
		ChessBoard::GetInstance()->checkmate = -1;
		//curTurn = -1;
		SetSceneState(SCENE_STATE::READY_SCENE);

		int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
		SendRoomState(roomNum, false, false);
	}
}

ChessGame::~ChessGame()
{
}

void ChessGame::Init(HWND hWnd, SOCKET sock, HINSTANCE g_hInst)
{
	lastTime = std::chrono::system_clock::now();
	playerIndex = 0;
	this->hWnd = hWnd;
	this->sock = sock;
	HDC hdc = GetDC(hWnd);
	cursor = { 0, 0 };
	curTurn = -1;
	reStartTime = 0.0f;

	gameDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, INGAME_WIDTH, INGAME_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(gameDC, hBitmap);

	BitMapManager::GetInstance()->Init(gameDC);
	LobbyManager::GetInstance()->Init(sock, hWnd, g_hInst);

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

	ChattingManager::GetInstance()->Input();

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
		CheckCheckmate(elapseTime);
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
		ChessBoard::GetInstance()->Render(gameDC);
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		DrawInGame(gameDC);
		ChessBoard::GetInstance()->Render(gameDC);
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}

	BitBlt(hdc, 0, 0, INGAME_WIDTH, INGAME_HEIGHT, gameDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

void ChessGame::Release()
{
	ChessBoard::GetInstance()->Release();
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
		CheckIsClickedBackButton(cursor.x, cursor.y);
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		ChessBoard::GetInstance()->MouseInput(cursor.x, cursor.y);
		CheckIsClickedBackButton(cursor.x, cursor.y);
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}
}
