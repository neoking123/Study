#pragma once
#include <Windows.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
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
#define MAX_ENEMY_NUM 4
#define MAX_SPAWN_NUM 20

class Tank;
class PlayerInputComponent;
class Tile;
class Enemy;
class EnemyInputComponent;

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
	vector<Tile*> tileVec;

	Tank* player;
	PlayerInputComponent* playerInput;
	vector<EnemyInputComponent*> enemyInputs;
	list<Enemy*> enemys;
	vector<Tank*> tanks;

	int spawnPointNum;
	float spawnTime;
	int spawnEnemyNum;
	int killCount;
	bool isDestroyedEgle;

	BattleCity();
	void LoadMap(string fileName);
	void DrawTiles();
	void DrawBackground();
	void CreateTile();
	void SpawnEnemy(float elapseTime);
	void DrawRemainEnemyNum(HDC hdc);
	void CheckWin();
	void DrawLifeCount(HDC hdc);
	void DrawFlag(HDC hdc);

public:
	~BattleCity();
	void Init(HWND hWnd);
	void Update();
	void Release();
	void Render();
	vector<Tile*> GetTiles();
	vector<Tank*> GetTanks();
	void DecreaseEnemyNum();
	void DestroyEgle();

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

