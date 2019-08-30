#include "BitMapManager.h"

BitMapManager* BitMapManager::pInstance = nullptr;

BitMapManager::BitMapManager()
{
}


BitMapManager::~BitMapManager()
{
}

void BitMapManager::Init(HDC hdc, HINSTANCE hInst)
{
	for (int i = 0; i < 20; i++)
	{
		BitMap* bitMap = new BitMap();
		Cards.push_back(bitMap);
		bitMap->Init(hdc, hInst, DOG + (i % 10));
	}
}
