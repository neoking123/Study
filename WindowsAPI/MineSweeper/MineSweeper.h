#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

const int WIDTH = 30;
const int HEIGHT = 16;

enum GAME_STATE
{

};

class Block;

class MineSweeper
{
private:
	static MineSweeper* pInstance;

	MineSweeper();

	vector<Block*> Blocks;
	HWND hWnd;
	SIZE size;
	int mineNum;
	int timer;

	void SpawnMine(int x, int y);
	void RandomSpawnMine();
	void DrawBackground(HDC hdc);
	void DrawMineCount(HDC hdc);
	void DrawTimer(HDC hdc);
	void DrawSmile(HDC hdc);


public:
	~MineSweeper();

	void Init(HDC hdc, HINSTANCE hInst, HWND hWnd);
	void Release();
	void Draw(HDC hdc);
	void Update();
	void Input(POINT pt, int clickButton);
	SIZE GetSize();
	Block* GetBlock(int index);
	void SendGamOverMessage();
	void OpenAllMines();

	static MineSweeper* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new MineSweeper();
		}
		return pInstance;
	}

	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
};

