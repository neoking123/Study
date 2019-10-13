#pragma once
#include <Windows.h>
#include <chrono>
#include <string>
#include "..\..\Common\Macro.h"
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

class CatchMind
{
private:
	static CatchMind* instance;
	HDC gameDC;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;
	HWND hWnd;
	HINSTANCE hInstance;
	POINT cursor;
	char nickName[32];
	float elapseTime;
	float reStartTime;
	chrono::system_clock::time_point lastTime;

	SCENE_STATE sceneState;

	CatchMind();
	void DrawLogin(HDC hdc);
	void DrawInRoom(HDC hdc);
	void DrawInGameFrame(HDC hdc);
	void DrawBackground(HDC hdc);
	void DrawPalette(HDC hdc);
	void DrawEraseAllButton(HDC hdc);
	void DrawTimer(HDC hdc);
	void DrawPlayersInfo(HDC hdc);
	void DrawPlayersInfoFrame(HDC hdc);
	void DrawKungyasToSelect(HDC hdc);
	bool CheckIsClickedStateButton(int x, int y);
	void CheckIsClickedBackButton(int x, int y);
	void LoginInput();

public:
	HWND hLoginEidt;
	int playerIndex;
	int curTurn;

	~CatchMind();
	void Init(HWND hWnd, HINSTANCE g_hInst);
	void Update();
	void Render();
	void Release();
	void MouseInput(int x, int y, int mouseState);
	void InitLogin();
	void SetSeceneState(SCENE_STATE newState);
	void DrawBackButton(HDC hdc);
	void DrawExitButton(HDC hdc);
	void DrawDockBar(HDC hdc);

	inline static CatchMind* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CatchMind();
		}
		return instance;
	}

	inline static void FreeInstance()
	{
		if (instance != nullptr)
		{
			SAFE_DELETE(instance);
		}
	}
};

