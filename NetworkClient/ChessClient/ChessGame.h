#pragma once
#include <Windows.h>
#include <chrono>
using namespace std;

#define FPS	60.0f
#define INGAME_WIDTH 1280
#define INGAME_HEIGHT 960
#define START_BUTTON_POSITION_X 800
#define START_BUTTON_POSITION_Y 500
#define BACK_BUTTON_POSITION_X 1150
#define BACK_BUTTON_POSITION_Y 925
#define DOCK_BAR_POSITION 921

enum MOUSE_STATE 
{
	CLICK_DOWN,
	CLICK_UP
};

enum SCENE_STATE
{
	LOGIN_SCENE,
	LOBY_SCENE,
	READY_SCENE,
	START_SCENE,
	INGAME_SCENE,
	RESULT_SCENE,
};

class ChessGame
{
private:
	static ChessGame* instance;

	HDC gameDC;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;
	HWND hWnd;
	SOCKET sock;
	POINT cursor;

	float elapseTime;
	float reStartTime;
	chrono::system_clock::time_point lastTime;

	SCENE_STATE sceneState;
	
	ChessGame();
	void DrawInRoom(HDC hdc);
	void DrawBackground(HDC hdc);
	void DrawChessBoard(HDC hdc);
	void DrawChessPieces(HDC hdc);
	void DrawInfoBackground(HDC hdc);
	void DrawInPlayerInfo(HDC hdc);
	void DrawRoomNum(HDC hdc);
	void DrawStartButton(HDC hdc);
	void DrawCurTurn(HDC hdc);
	void DrawCheckState(HDC hdc);
	void DrawChat(HDC hdc);
	bool CheckIsClickedStateButton(int x, int y);
	void CheckIsClickedBackButton(int x, int y);
	void SendRoomState(int roomNum, bool isStart = false, bool canStart = false);
	void SendBackToLobby();
	void DrawRoomState_Debug(HDC hdc);
	void CheckStart();
	void DrawInGame(HDC hdc);
	void InGameInit();
	void CheckCheckmate(float elapseTime);

public:
	int playerIndex;
	int curTurn;

	~ChessGame();
	void Init(HWND hWnd, SOCKET sock, HINSTANCE g_hInst);
	void Update();
	void Render();
	void Release();
	void MouseInput(int x, int y, int mouseState);
	void DrawBackButton(HDC hdc);
	void DrawExitButton(HDC hdc);
	void DrawDockBar(HDC hdc);

	inline HDC GetGameDC()
	{
		return gameDC;
	}
	
	inline SOCKET GetSock()
	{
		return sock;
	}

	inline void SetSceneState(SCENE_STATE newSceneState)
	{
		sceneState = newSceneState;
	}

	inline static ChessGame* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ChessGame();
		}
		return instance;
	}

	inline void FreeInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
};

