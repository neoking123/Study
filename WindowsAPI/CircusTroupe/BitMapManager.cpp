#include "BitMapManager.h"
#include "Macro.h"

BitMapManager* BitMapManager::pInstance = nullptr;

BitMapManager::BitMapManager()
{
}


BitMapManager::~BitMapManager()
{
}

void BitMapManager::Init(HINSTANCE hInst, HDC hdc)
{
	/*HDC MemDC;
	MemDC = CreateCompatibleDC(hdc);
	g_MemDC[0] = CreateCompatibleDC(hdc);
	g_hBitMap[0] = CreateCompatibleBitmap(hdc, 870, 512);
	g_hOld[0] = (HBITMAP)SelectObject(g_MemDC[0], g_hBitMap[0]);*/

	BitMaps.reserve(20);

	for (int i = 0; i < BITMAP_RES::END; i++)
	{
		BitMap* bitMap = new BitMap();
		bitMap->Init(hdc, hInst, BITMAP_RES::BACK + i);
		BitMaps.push_back(bitMap);
	}
}

BitMap * BitMapManager::GetBitMap(int id)
{
	if (BitMaps.at(id))
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
