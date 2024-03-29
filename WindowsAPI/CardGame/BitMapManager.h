#pragma once
#include <vector>
#include "BitMap.h"
using namespace std;

enum CARD_LIST
{
	DOG,
	TIGER,
	DUCK,
	ELEPHANT,
	COW,
	HORSE,
	CAT,
	MONKEY,
	FROG,
	CHICKEN,
	BACK,
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

	void Init(HDC hdc, HINSTANCE hInst);
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

