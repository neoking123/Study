#include "CatchMind.h"
#include "BitMapManager.h"
#include "LobbyManager.h"
#include "ChattingManager.h"
#include "..\..\Common\NetworkManager.h"
#include "SketchBook.h"

CatchMind* CatchMind::instance = nullptr;

CatchMind::CatchMind()
{
}

void CatchMind::DrawInRoom(HDC hdc)
{
	DrawBackground(hdc);
	DrawInGameFrame(hdc);
	DrawPalette(hdc);
	DrawEraseAllButton(hdc);
	DrawTimer(hdc);
	DrawDockBar(hdc);
	DrawBackButton(hdc);
	DrawExitButton(hdc);
	ChattingManager::GetInstance()->DrawChat(hdc);
}
void CatchMind::DrawInGameFrame(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_GAME_FRAME)->Draw(hdc, 342, 130);
}

void CatchMind::DrawBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_BACK)->Draw(hdc, 0, 0, 2, 2);
}

void CatchMind::DrawPalette(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_BALCK)->Draw(hdc, 400, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_RED)->Draw(hdc, 435, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_BLUE)->Draw(hdc, 470, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_GREEN)->Draw(hdc, 505, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_YELLOW)->Draw(hdc, 540, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_WHITE)->Draw(hdc, 575, 500);

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ERASE_BUTTON)->Draw(hdc, 620, 500);
}

void CatchMind::DrawEraseAllButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ERASE_ALL_BUTTON)->Draw(hdc, 720, 500);
}

void CatchMind::DrawTimer(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::TIMER_FRAME)->Draw(hdc, 380, 580);
}

bool CatchMind::CheckIsClickedStateButton(int x, int y)
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
				NetworkManager::GetInstance()->SendRoomState(roomNum, isStart);
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
				NetworkManager::GetInstance()->SendRoomState(roomNum, canStart);
			}
			else
			{
				canStart = true;
				LobbyManager::GetInstance()->SetCanStart(roomNum, canStart);
				NetworkManager::GetInstance()->SendRoomState(roomNum, canStart);
			}
		}
		return true;
	}
	return false;
}

void CatchMind::CheckIsClickedBackButton(int x, int y)
{
	if (x > BACK_BUTTON_POSITION_X && x < BACK_BUTTON_POSITION_X + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->GetSize().cx
		&& y > BACK_BUTTON_POSITION_Y && y < BACK_BUTTON_POSITION_Y + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->GetSize().cy)
	{
		sceneState = SCENE_STATE::LOBY_SCENE;
		LobbyManager::GetInstance()->ActivateCreateRoom();
		//ChessBoard::GetInstance()->CleanPieces();
		//ChessBoard::GetInstance()->Init();
		curTurn = -1;
		//SendBackToLobby();
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
		NetworkManager::GetInstance()->SendBackToLobby(playerIndex, roomNum);
	}
}

CatchMind::~CatchMind()
{
}

void CatchMind::Init(HWND hWnd, HINSTANCE g_hInst)
{
	lastTime = std::chrono::system_clock::now();
	playerIndex = 0;
	this->hWnd = hWnd;
	HDC hdc = GetDC(hWnd);
	curTurn = -1;
	reStartTime = 0.0f;

	gameDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, INGAME_WIDTH, INGAME_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(gameDC, hBitmap);

	BitMapManager::GetInstance()->Init(gameDC);
	LobbyManager::GetInstance()->Init(hWnd, g_hInst);
	SketchBook::GetInstance()->Init();

	sceneState = SCENE_STATE::LOBY_SCENE;
	//InGameInit();
	ReleaseDC(hWnd, hdc);
}

void CatchMind::Update()
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

void CatchMind::Render()
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
		SketchBook::GetInstance()->Render(gameDC);
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		//DrawInGame(gameDC);
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}

	BitBlt(hdc, 0, 0, INGAME_WIDTH, INGAME_HEIGHT, gameDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

void CatchMind::Release()
{
	BitMapManager::GetInstance()->Release();
}

void CatchMind::MouseInput(int x, int y, int mouseState)
{
	cursor = { x, y };
	/*if (mouseState == MOUSE_STATE::CLICK_DOWN)
	{
		cursor = { x, y };
	}
	else if (mouseState == MOUSE_STATE::CLICK_UP)
	{
		cursor = { x, y };
	}*/

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
		SketchBook::GetInstance()->MouseInput(cursor.x, cursor.y, mouseState);
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		//ChessBoard::GetInstance()->MouseInput(cursor.x, cursor.y);
		CheckIsClickedBackButton(cursor.x, cursor.y);
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}
}

void CatchMind::SetSeceneState(SCENE_STATE newState)
{
	sceneState = newState;
}

void CatchMind::DrawBackButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->Draw(hdc, BACK_BUTTON_POSITION_X, BACK_BUTTON_POSITION_Y);
}

void CatchMind::DrawExitButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::EXIT_ICON)->Draw(hdc, BACK_BUTTON_POSITION_X + 50, BACK_BUTTON_POSITION_Y);
}

void CatchMind::DrawDockBar(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::DOCK_BAR)->Draw(hdc, 0, DOCK_BAR_POSITION, 2, 1);
}