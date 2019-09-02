#include "Block.h"
#include "BitMap.h"
#include "BitMapManager.h"

Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(int x, int y, BLOCK_STATE _state)
{
	bitMap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::RES_0);
	position.x = x;
	position.y = y;
	state = _state;
	size.cx = bitMap->GetSize().cx;
	size.cy = bitMap->GetSize().cy;
	hasMine = false;
}

void Block::Draw(HDC hdc)
{
	bitMap = BitMapManager::GetInstance()->GetBitMap(state);
	bitMap->Draw(hdc, position.x, position.y);
}

void Block::SetState(BLOCK_STATE _state)
{
	state = _state;
}

void Block::SetHasMine(bool _hasMine)
{
	hasMine = _hasMine;
}

CLICK_STATE Block::CheckClick(POINT pt)
{
	if (pt.x > position.x && pt.x < position.x + size.cx && pt.y > position.y && pt.y < position.y + size.cy)
	{
		if (hasMine)
		{
			SetState(BLOCK_STATE::MINE);
			return CLICK_STATE::MINE_CLICK;
		}
		else if(!hasMine)
		{
			SetState(BLOCK_STATE::CLICKED);

			return CLICK_STATE::BLOCK_CLICK;
		}
	}
	return CLICK_STATE::NONE_BLOCK_CLICK;
}
