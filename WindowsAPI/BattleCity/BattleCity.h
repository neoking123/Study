#pragma once
#include <Windows.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Macro.h"
using namespace std;

#define FPS	100.0f
#define MAP_WIDTH 32
#define MAP_HEIGHT 32
#define SCREEN_WIDE 550
#define SCREEN_HEIGHT 460
#define MAP_MARGINE_WIDTH 24
#define MAP_MARGINE_HEIGHT 24
#define TILE_WIDTH_NUM 13
#define TILE_HEIGHT_NUM 13
#define TILE_SIZE 32

class Tank;
class PlayerInputComponent;
class Tile;

class BattleCity
{
private:
	static BattleCity* pInstance;

	HDC gameDC;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;
	HWND hWnd;
	float elapseTime;
	chrono::system_clock::time_point lastTime;
	int tiles[MAP_HEIGHT][MAP_WIDTH];
	Tank* player;
	PlayerInputComponent* playerInput;
	vector<Tile*> tileVec;

	BattleCity();
	void LoadMap(string fileName);
	void DrawTiles();
	void DrawBackground();
	void CreateTile();

public:
	~BattleCity();
	void Init(HWND hWnd);
	void Update();
	void Release();
	void Render();
	vector<Tile*> GetTiles();

	static BattleCity* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new BattleCity();
		}
		return pInstance;
	}

	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			SAFE_DELETE(pInstance);

		}
	}
};

