#pragma once
#include <vector>
#include "BitMap.h"
using namespace std;

enum BITMAP_RES
{
	CHESS_BOARD,
	KING_W,
	QUEEN_W,
	BISHOP_W,
	KNIGHT_W,
	ROOK_W,
	PAWN_W,
	KING_B,
	QUEEN_B,
	BISHOP_B,
	KNIGHT_B,
	ROOK_B,
	PAWN_B,
	LOBY_BACK,
	LOBY_PLAYER_INFO,
	LOBY_ROOM_FRAME,
	LOBY_ROOM_WAITING,
	LOBY_ROOM_FULL,
	LOBY_ROOM_PLAYING,
	LOBY_ROOM_PLAYER_ICON,
	LOBY_ROOM_ICON_0,
	LOBY_ROOM_ICON_1,
	LOBY_ROOM_KEY_ICON,
	LOBY_ROOM_BUTTON_CREATE,
	EXIT_ICON,
	BUTTON_READY,
	BUTTON_START,
	IN_ROOM_INFO_BACK,
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

