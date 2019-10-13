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
#define KUNGYA_SIZE 80
#define PALETTE_SIZE 30

enum MOUSE_STATE
{
	LCLICK_DOWN,
	LCLICK_UP,
	RCLICK_DOWN,
	RCLICK_UP
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
	bool isSelectKungya;
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
	void DrawAllPlayers(HDC hdc);
	void DrawKungyasToSelect(HDC hdc);
	void DrawSelectedKungya(HDC hdc);
	void DrawLoginInfo(HDC hdc);
	bool CheckIsClickedStateButton(int x, int y);
	void CheckIsClickedBackButton(int x, int y);
	void CheckIsClickedKungya(int x, int y);
	void CheckIsClickedPalette(int x, int y, int mouseState);
	void CheckIsCliekedEraseAll(int x, int y, int mouseState);
	void LoginInput();

public:
	HWND hLoginEidt;
	int playerIndex;
	int curTurn;
	int kungyaNum;

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

	inline SCENE_STATE GetSceneState()
	{
		return sceneState;
	}

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

