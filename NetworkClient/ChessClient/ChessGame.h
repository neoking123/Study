#pragma once
#include <Windows.h>
#include <chrono>
using namespace std;

#define FPS	60.0f
#define INGAME_WIDTH 1280
#define INGAME_HEIGHT 960
#define START_BUTTON_POSITION_X 800
#define START_BUTTON_POSITION_Y 500

class ChessPiece;

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

	ChessPiece* testPiece;

	HDC gameDC;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;
	HWND hWnd;
	SOCKET sock;
	POINT cursor;

	float elapseTime;
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
	void DrawButton(HDC hdc);
	bool CheckIsClickedStateButton(int x, int y);
	void SendRoomState(int roomNum, bool isStart = false, bool canStart = false);
	void DrawRoomState_Debug(HDC hdc);
	void CheckStart();
	void DrawInGame(HDC hdc);
	void InGameInit();

public:
	int playerIndex;

	~ChessGame();
	void Init(HWND hWnd, SOCKET sock);
	void Update();
	void Render();
	void Release();
	void MouseInput(int x, int y, int mouseState);
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

