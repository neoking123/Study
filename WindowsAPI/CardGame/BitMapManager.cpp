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
	BitMaps.reserve(10);

	for (int i = 0; i < CARD_LIST::END; i++)
	{
		BitMap* bitMap = new BitMap();
		BitMaps.push_back(bitMap);
		bitMap->Init(hdc, hInst, CARD_LIST::DOG + i);
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
