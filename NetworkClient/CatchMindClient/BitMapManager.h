#pragma once
#include <vector>
#include "BitMap.h"
using namespace std;

enum BITMAP_RES
{
	LOBY_BACK,
	LOBY_PLAYER_INFO,
	LOBY_ROOM_FRAME,
	LOBY_ROOM_WAITING,
	LOBY_ROOM_FULL,
	LOBY_ROOM_PLAYING,
	LOBY_ROOM_PLAYER_ICON,
	LOBY_ROOM_KEY_ICON,
	LOBY_ROOM_BUTTON_CREATE,
	EXIT_ICON,
	BUTTON_READY,
	BUTTON_START,
	IN_ROOM_INFO_BACK,
	LOBBY_CHAT,
	BUTTON_BACK,
	DOCK_BAR,
	LOBY_ROOM_ICON_0,
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

