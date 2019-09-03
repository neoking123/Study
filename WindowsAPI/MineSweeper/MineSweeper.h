#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

extern int WIDTH;
extern int HEIGHT;

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
	int flagNum;
	int timer;
	int checkCount;
	bool isEnd;
	bool isWin;

	void SpawnMine(int x, int y);
	void RandomSpawnMine(int mineNum);
	void DrawBackground(HDC hdc);
	void DrawMineCount(HDC hdc);
	void DrawTimer(HDC hdc);
	void DrawSmile(HDC hdc);
	void CheckWin();
	void CheckSmileClick(POINT pt);

public:
	~MineSweeper();

	void Init(HDC hdc, HINSTANCE hInst, HWND hWnd);
	void ReInit(int _mineNum);
	void Release();
	void Draw(HDC hdc);
	void Update();
	void Input(POINT pt, int clickButton);
	SIZE GetSize();
	Block* GetBlock(int index);
	void SendGamOverMessage();
	void SendWinMessage();
	void OpenAllMines();
	void PlusFlagNum();
	void MinusFlagNum();
	void EndGame();


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

