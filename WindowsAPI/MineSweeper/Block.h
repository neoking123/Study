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
	bool isOpen;
	bool isFlag;
	bool tempOpen;
	bool ClickOpenBlock;
	int index;
	int nearMineNum;

	int CheckNearMines();

public:
	Block();
	~Block();

	void Init(int x, int y, BLOCK_STATE _state, int _index);
	void Draw(HDC hdc);
	CLICK_STATE CheckClick(POINT pt, int clickButton);
	void SetHasMine(bool _hasMine);
	bool GetHasMine();
	bool GetIsOpen();
	BLOCK_STATE GetState();
	void SetState(BLOCK_STATE _state);
	void CheckNearBlocks();
	int CheckNearFlag();
	void ClickNear();
	void ButtonUp();
	bool IsTempOpen();
};