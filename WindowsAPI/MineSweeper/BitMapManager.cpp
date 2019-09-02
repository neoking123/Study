#include "BitMapManager.h"
#include "Macro.h"

BitMapManager* BitMapManager::pInstance = nullptr;

BitMapManager::BitMapManager()
{
}


BitMapManager::~BitMapManager()
{
}

void BitMapManager::Init(HDC hdc, HINSTANCE hInst)
{
	BitMaps.reserve(20);

	for (int i = 0; i < BITMAP_RES::END; i++)
	{
		BitMap* bitMap = new BitMap();
		bitMap->Init(hdc, hInst, BITMAP_RES::RES_0 + i);
		BitMaps.push_back(bitMap);
	}
}

BitMap * BitMapManager::GetBitMap(int id)
{
	if (BitMaps[id])
		return BitMaps[id];
	else
		return nullptr;
}

void BitMapManager::Release()
{
	for (auto iter = BitMaps.begin(); iter != BitMaps.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}
