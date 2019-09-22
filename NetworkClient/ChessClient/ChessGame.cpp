#include "ChessGame.h"
#include "BitMapManager.h"
#include "LobbyManager.h"

ChessGame* ChessGame::instance = nullptr;

ChessGame::ChessGame()
{
}

ChessGame::~ChessGame()
{
}

void ChessGame::Init(HWND hWnd)
{
	lastTime = std::chrono::system_clock::now();

	this->hWnd = hWnd;
	HDC hdc = GetDC(hWnd);
	cursor = { 0, 0 };

	gameDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, INGAME_WIDTH, INGAME_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(gameDC, hBitmap);

	BitMapManager::GetInstance()->Init(gameDC);
	LobbyManager::GetInstance()->Init();

	sceneState = SCENE_STATE::LOBY_SCENE;

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
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}

	BitBlt(hdc, 0, 0, INGAME_WIDTH, INGAME_HEIGHT, gameDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

void ChessGame::Release()
{
	LobbyManager::GetInstance()->Release();
	BitMapManager::GetInstance()->Release();
}

void ChessGame::MouseInput(int x, int y, int mouseState)
{
	if (mouseState == MOUSE_STATE::CLICK_DOWN)
	{
		cursor.x = x;
		cursor.y = y;
	}
	else if(mouseState == MOUSE_STATE::CLICK_UP)
	{
		cursor.x = 0;
		cursor.y = 0;
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
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}
}
