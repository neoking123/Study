#include "CatchMind.h"
#include "BitMapManager.h"
#include "LobbyManager.h"
#include "ChattingManager.h"
#include "..\..\Common\NetworkManager.h"

CatchMind* CatchMind::instance = nullptr;

CatchMind::CatchMind()
{
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
		//DrawInRoom(gameDC);
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
	if (mouseState == MOUSE_STATE::CLICK_DOWN)
	{
		cursor = { x, y };
	}
	else if (mouseState == MOUSE_STATE::CLICK_UP)
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
