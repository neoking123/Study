#pragma once
#include <vector>
#include "BitMap.h"
using namespace std;

enum BITMAP_RES
{
	BLOCK_0,
	BLOCK_1,
	BLOCK_2,
	BLOCK_3,
	BLOCK_4,
	BLOCK_5,
	BLOCK_6,
	BLOCK_7,
	BLOCK_8,
	BLOCK_9,
	BLOCK_10,
	BLOCK_11,
	BLOCK_12,
	BLOCK_13,
	BLOCK_14,
	E_DOWN_0,
	E_DOWN_1,
	E_LEFT_0,
	E_LEFT_1,
	E_RIGHT_0,
	E_RIGHT_1,
	E_UP_0,
	E_UP_1,
	E_DOWN_2,
	E_LEFT_2,
	E_RIGHT_2,
	E_UP_2,
	ENERMY_ICON,
	EXPLOSION_0,
	EXPLOSION_1,
	EXPLOSION_2,
	EXPLOSION_3,
	EXPLOSION_4,
	MISSILE_0,
	PLAYER_ICON,
	SHIELD_0,
	SHIELD_1,
	STAGE_ICON,
	TANK_DOWN_0,
	TANK_DOWN_1,
	TANK_LEFT_0,
	TANK_LEFT_1,
	TANK_RIGHT_0,
	TANK_RIGHT_1,
	TANK_UP_0,
	TANK_UP_1,
	BACK_BLACK,
	BLOCK_15,
	BACK_GREY,
	MISSILE_1,
	MISSILE_2,
	MISSILE_3,
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

	void Init(HDC hdc);
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

