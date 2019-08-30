#pragma once
#include <vector>
#include "BitMap.h"
using namespace std;

enum CARD_LIST
{
	DOG = 101,
	TIGER,
	DUCK,
	ELEPHANT,
	COW,
	HORSE,
	CAT,
	MONKEY,
	FROG,
	CHICKEN,
	BACK
};

class BitMapManager
{
private:
	static BitMapManager* pInstance;
	BitMapManager();

	vector<BitMap*> Cards;

public:
	~BitMapManager();

	void Init(HDC hdc, HINSTANCE hInst);
};

