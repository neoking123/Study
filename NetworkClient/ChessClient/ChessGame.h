#pragma once
#include <Windows.h>
#include <chrono>
using namespace std;

#define FPS	60.0f
#define INGAME_WIDTH 1280
#define INGAME_HEIGHT 960

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
	POINT cursor;

	float elapseTime;
	chrono::system_clock::time_point lastTime;

	SCENE_STATE sceneState;

	ChessGame();

public:
	~ChessGame();
	void Init(HWND hWnd);
	void Update();
	void Render();
	void Release();
	void MouseInput(int x, int y, int mouseState);

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

