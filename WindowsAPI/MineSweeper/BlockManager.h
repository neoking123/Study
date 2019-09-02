#pragma once
#include <vector>
#include <Windows.h>
using namespace std;

class Block;
enum CLICK_STATE;

class BlockManager
{
private:
	BlockManager();

	static BlockManager* pInstance;

	vector<Block*> Blocks;
	SIZE size;

public:
	~BlockManager();

	void Init(int width, int height);
	Block* GetBlock(int index);
	CLICK_STATE Input(POINT pt);
	void Draw(HDC hdc);
	void Release();
	void SpawnMine(int x, int y);
	void RandomSpawnMine();

	static BlockManager* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new BlockManager();
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

