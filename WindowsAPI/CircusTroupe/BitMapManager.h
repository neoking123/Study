#pragma once
#include <vector>
#include "BitMap.h"
using namespace std;

enum BITMAP_RES
{
	BACK,
	BACK_DECO,
	BACK_NORMAL,
	BACK_NORMAL2,
	CASH,
	DEATH,
	ENEMY,
	ENEMY_1B,
	ENEMY_1F,
	ENEMY_B,
	ENEMY_F,
	ENEMY_L,
	ENEMY_L_B,
	ENEMY_L_F,
	ENEMY1,
	FRONT,
	FRONT2,
	GOAL,
	ICON,
	MITER,
	PLAYER0,
	PLAYER1,
	PLAYER2,
	STAR,
	STAR1,
	STAR2,
	WIN,
	WIN2,
	END
};

class BitMapManager
{
private:
	static BitMapManager* pInstance;
	BitMapManager();

	vector<BitMap*> BitMaps;

public:
	~BitMapManager();

	void Init(HINSTANCE hInst, HDC hdc);
	BitMap* GetBitMap(int id);
	void Release();


	static BitMapManager* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new BitMapManager();
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

