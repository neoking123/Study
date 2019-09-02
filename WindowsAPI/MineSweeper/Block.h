#pragma once
#include <Windows.h>
class BitMap;

enum BLOCK_STATE
{
	NONECLICK,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	MINE,
	FLAG,
	CLICKED
};

enum CLICK_STATE
{
	NONE_BLOCK_CLICK,
	MINE_CLICK,
	BLOCK_CLICK
};

class Block
{
private:
	BitMap* bitMap;
	POINT position;
	BLOCK_STATE state;
	SIZE size;
	bool hasMine;

public:
	Block();
	~Block();

	void Init(int x, int y, BLOCK_STATE _state);
	void Draw(HDC hdc);
	CLICK_STATE CheckClick(POINT pt);
	void SetHasMine(bool _hasMine);
	void SetState(BLOCK_STATE _state);
};

