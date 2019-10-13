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
	IN_GAME_FRAME,
	SKETCH_BOOK,
	TIMER_FRAME,
	ERASE_ALL_BUTTON,
	ERASE_BUTTON,
	COLOR_BUTTON_BALCK,
	COLOR_BUTTON_RED,
	COLOR_BUTTON_BLUE,
	COLOR_BUTTON_GREEN,
	COLOR_BUTTON_YELLOW,
	COLOR_BUTTON_WHITE,
	PLAYER_INFO_FRAME,
	KUNGYA_0,
	KUNGYA_1,
	KUNGYA_2,
	KUNGYA_3,
	KUNGYA_4,
	KUNGYA_5,
	KUNGYA_6,
	KUNGYA_7,
	KUNGYA_8,
	KUNGYA_9,
	KUNGYA_10,
	KUNGYA_11,
	LOBY_PLAYER_INFO_FRAME,
	LOBY_PLAYER_INFO_ROOMNUM,
	KUNGYA_SELECT_FRAME,
	LOGIN_INFO_FRAME,
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

