#include "Block.h"
#include "BitMap.h"
#include "BitMapManager.h"
#include "MineSweeper.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Init(int x, int y, BLOCK_STATE _state, int _index)
{
	bitMap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::RES_0);
	position.x = x;
	position.y = y;
	state = _state;
	size.cx = bitMap->GetSize().cx;
	size.cy = bitMap->GetSize().cy;
	hasMine = false;
	isOpen = false;
	isFlag = false;
	tempOpen = false;
	ClickOpenBlock = false;
	index = _index;
	nearMineNum = 0;
}

void Block::Draw(HDC hdc)
{
	bitMap = BitMapManager::GetInstance()->GetBitMap(state);
	bitMap->Draw(hdc, position.x, position.y);
}

void Block::SetState(BLOCK_STATE _state)
{
	state = _state;

	if (state == BLOCK_STATE::FLAG)
	{
		isFlag = true;
	}
	else if (state != BLOCK_STATE::NONECLICK)
	{
		isOpen = true;
		tempOpen = false;
	}
	else
	{
		isFlag = false;
		isOpen = false;
		tempOpen = false;
	}
}

int Block::CheckNearMines()
{
	nearMineNum = 0;
	//앞
	if (index + 1 < WIDTH * HEIGHT && (index + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + 1)->hasMine)
			nearMineNum++;
	}

	//뒤
	if (index - 1 >= 0 && (index - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - 1)->hasMine)
			nearMineNum++;
	}

	//아래
	if (index + WIDTH < WIDTH * HEIGHT)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH)->hasMine)
			nearMineNum++;
	}

	//위
	if (index - WIDTH >= 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH)->hasMine)
			nearMineNum++;
	}

	//위-뒤
	if (index - WIDTH - 1 >= 0 && (index - WIDTH - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->hasMine)
			nearMineNum++;
	}

	//위-앞
	if (index - WIDTH + 1 >= 0 && (index - WIDTH + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->hasMine)
			nearMineNum++;
	}

	//아래-앞
	if (index + WIDTH + 1 < WIDTH * HEIGHT && (index + WIDTH + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->hasMine)
			nearMineNum++;
	}

	//아래-뒤
	if (index + WIDTH - 1 < WIDTH * HEIGHT && (index + WIDTH - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->hasMine)
			nearMineNum++;
	}

	return nearMineNum;
}

void Block::CheckNearBlocks()
{
	CheckNearMines();

	if (nearMineNum == 0)
	{
		SetState(BLOCK_STATE::CLICKED);
	}
	else if(nearMineNum > 0 && nearMineNum <= 8)
	{
		SetState((BLOCK_STATE)nearMineNum);
	}

	// 재귀

	if (index + 1 < WIDTH * HEIGHT && (index + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + 1)->GetState() == BLOCK_STATE::NONECLICK 
			&& !(MineSweeper::GetInstance()->GetBlock(index + 1)->hasMine)
			&& state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index + 1)->CheckNearBlocks();
		}
	}

	if (index - 1 >= 0 && (index - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - 1)->GetState() == BLOCK_STATE::NONECLICK
			&& !(MineSweeper::GetInstance()->GetBlock(index - 1)->hasMine)
			&& state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index - 1)->CheckNearBlocks();
		}
	}

	if (index + WIDTH < WIDTH * HEIGHT)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH)->GetState() == BLOCK_STATE::NONECLICK
			&& !(MineSweeper::GetInstance()->GetBlock(index + WIDTH)->hasMine)
			&& state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index + WIDTH)->CheckNearBlocks();
		}
	}

	if (index - WIDTH >= 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH)->GetState() == BLOCK_STATE::NONECLICK
			&& !(MineSweeper::GetInstance()->GetBlock(index - WIDTH)->hasMine)
			&& state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index - WIDTH)->CheckNearBlocks();
		}
	}

	if (index - WIDTH - 1 >= 0 && (index - WIDTH - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->GetState() == BLOCK_STATE::NONECLICK
			&& !(MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->hasMine)
			&& state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->CheckNearBlocks();
		}
	}

	if (index - WIDTH + 1 >= 0 && (index - WIDTH + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->GetState() == BLOCK_STATE::NONECLICK
			&& !(MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->hasMine)
			&& state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->CheckNearBlocks();
		}
	}

	if (index + WIDTH + 1 < WIDTH * HEIGHT && (index + WIDTH + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->GetState() == BLOCK_STATE::NONECLICK
			&& !(MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->hasMine)
			&& state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->CheckNearBlocks();
		}
	}

	if (index + WIDTH - 1 < WIDTH * HEIGHT && (index + WIDTH - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->GetState() == BLOCK_STATE::NONECLICK
			&& !(MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->hasMine)
			&& state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->CheckNearBlocks();
		}
	}
}

int Block::CheckNearFlag()
{
	int nearFlagNum = 0;

	//앞
	if (index + 1 < WIDTH * HEIGHT && (index + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + 1)->isFlag)
			nearFlagNum++;
	}

	//뒤
	if (index - 1 >= 0 && (index - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - 1)->isFlag)
			nearFlagNum++;
	}

	//아래
	if (index + WIDTH < WIDTH * HEIGHT)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH)->isFlag)
			nearFlagNum++;
	}

	//위
	if (index - WIDTH >= 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH)->isFlag)
			nearFlagNum++;
	}

	//위-뒤
	if (index - WIDTH - 1 >= 0 && (index - WIDTH - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->isFlag)
			nearFlagNum++;
	}

	//위-앞
	if (index - WIDTH + 1 >= 0 && (index - WIDTH + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->isFlag)
			nearFlagNum++;
	}

	//아래-앞
	if (index + WIDTH + 1 < WIDTH * HEIGHT && (index + WIDTH + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->isFlag)
			nearFlagNum++;
	}

	//아래-뒤
	if (index + WIDTH - 1 < WIDTH * HEIGHT && (index + WIDTH - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->isFlag)
			nearFlagNum++;
	}

	return nearFlagNum;
}

void Block::ClickNear()
{
	int flagNum = CheckNearFlag();

	if (state == BLOCK_STATE::CLICKED)
		return;

	if (nearMineNum != flagNum)
	{
		//앞
		if (index + 1 < WIDTH * HEIGHT && (index + 1) % WIDTH != 0)
		{
			if (MineSweeper::GetInstance()->GetBlock(index + 1)->GetState() == BLOCK_STATE::NONECLICK)
			{
				MineSweeper::GetInstance()->GetBlock(index + 1)->SetState(BLOCK_STATE::CLICKED);
				MineSweeper::GetInstance()->GetBlock(index + 1)->tempOpen = true;
			}	
		}

		//뒤
		if (index - 1 >= 0 && (index - 1) % WIDTH != WIDTH - 1)
		{
			if (MineSweeper::GetInstance()->GetBlock(index - 1)->GetState() == BLOCK_STATE::NONECLICK)
			{
				MineSweeper::GetInstance()->GetBlock(index - 1)->SetState(BLOCK_STATE::CLICKED);
				MineSweeper::GetInstance()->GetBlock(index - 1)->tempOpen = true;
			}
		}

		//아래
		if (index + WIDTH < WIDTH * HEIGHT)
		{
			if (MineSweeper::GetInstance()->GetBlock(index + WIDTH)->GetState() == BLOCK_STATE::NONECLICK)
			{
				MineSweeper::GetInstance()->GetBlock(index + WIDTH)->SetState(BLOCK_STATE::CLICKED);
				MineSweeper::GetInstance()->GetBlock(index + WIDTH)->tempOpen = true;
			}
		}

		//위
		if (index - WIDTH >= 0)
		{
			if (MineSweeper::GetInstance()->GetBlock(index - WIDTH)->GetState() == BLOCK_STATE::NONECLICK)
			{
				MineSweeper::GetInstance()->GetBlock(index - WIDTH)->SetState(BLOCK_STATE::CLICKED);
				MineSweeper::GetInstance()->GetBlock(index - WIDTH)->tempOpen = true;
			}
		}

		//위-뒤
		if (index - WIDTH - 1 >= 0 && (index - WIDTH - 1) % WIDTH != WIDTH - 1)
		{
			if (MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->GetState() == BLOCK_STATE::NONECLICK)
			{
				MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->SetState(BLOCK_STATE::CLICKED);
				MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->tempOpen = true;
			}
		}

		//위-앞
		if (index - WIDTH + 1 > 0 && (index - WIDTH + 1) % WIDTH != 0)
		{
			if (MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->GetState() == BLOCK_STATE::NONECLICK)
			{
				MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->SetState(BLOCK_STATE::CLICKED);
				MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->tempOpen = true;
			}
		}

		//아래-앞
		if (index + WIDTH + 1 < WIDTH * HEIGHT && (index + WIDTH + 1) % WIDTH != 0)
		{
			if (MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->GetState() == BLOCK_STATE::NONECLICK)
			{
				MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->SetState(BLOCK_STATE::CLICKED);
				MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->tempOpen = true;
			}
		}

		//아래-뒤
		if (index + WIDTH - 1 < WIDTH * HEIGHT && (index + WIDTH - 1) % WIDTH != WIDTH - 1)
		{
			if (MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->GetState() == BLOCK_STATE::NONECLICK)
			{
				MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->SetState(BLOCK_STATE::CLICKED);
				MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->tempOpen = true;
			}
		}
	}
	else
	{
		int matchCount = 0;

		//앞
		if (index + 1 < WIDTH * HEIGHT && (index + 1) % WIDTH != 0)
		{
			if (MineSweeper::GetInstance()->GetBlock(index + 1)->isFlag 
				&& MineSweeper::GetInstance()->GetBlock(index + 1)->hasMine)
			{
				matchCount++;
			}
		}

		//뒤
		if (index - 1 >= 0 && (index - 1) % WIDTH != WIDTH - 1)
		{
			if (MineSweeper::GetInstance()->GetBlock(index - 1)->isFlag
				&& MineSweeper::GetInstance()->GetBlock(index - 1)->hasMine)
			{
				matchCount++;
			}
		}

		//아래
		if (index + WIDTH < WIDTH * HEIGHT)
		{
			if (MineSweeper::GetInstance()->GetBlock(index + WIDTH)->isFlag
				&& MineSweeper::GetInstance()->GetBlock(index + WIDTH)->hasMine)
			{
				matchCount++;
			}
		}

		//위
		if (index - WIDTH >= 0)
		{
			if (MineSweeper::GetInstance()->GetBlock(index - WIDTH)->isFlag
				&& MineSweeper::GetInstance()->GetBlock(index - WIDTH)->hasMine)
			{
				matchCount++;
			}
		}

		//위-뒤
		if (index - WIDTH - 1 >= 0 && (index - WIDTH - 1) % WIDTH != WIDTH - 1)
		{
			if (MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->isFlag
				&& MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->hasMine)
			{
				matchCount++;
			}
		}

		//위-앞
		if (index - WIDTH + 1 > 0 && (index - WIDTH + 1) % WIDTH != 0)
		{
			if (MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->isFlag
				&& MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->hasMine)
			{
				matchCount++;
			}
		}

		//아래-앞
		if (index + WIDTH + 1 < WIDTH * HEIGHT && (index + WIDTH + 1) % WIDTH != 0)
		{
			if (MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->isFlag
				&& MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->hasMine)
			{
				matchCount++;
			}
		}

		//아래-뒤
		if (index + WIDTH - 1 < WIDTH * HEIGHT && (index + WIDTH - 1) % WIDTH != WIDTH - 1)
		{
			if (MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->isFlag
				&& MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->hasMine)
			{
				matchCount++;
			}
		}

		if (matchCount != nearMineNum)
		{
			MineSweeper::GetInstance()->SendGamOverMessage();
		}
		else
		{
			//앞
			if (index + 1 < WIDTH * HEIGHT && (index + 1) % WIDTH != 0)
			{
				if (MineSweeper::GetInstance()->GetBlock(index + 1)->state == BLOCK_STATE::NONECLICK)
				{
					MineSweeper::GetInstance()->GetBlock(index + 1)->CheckNearBlocks();
				}
			}

			//뒤
			if (index - 1 >= 0 && (index - 1) % WIDTH != WIDTH - 1)
			{
				if (MineSweeper::GetInstance()->GetBlock(index - 1)->state == BLOCK_STATE::NONECLICK)
				{
					MineSweeper::GetInstance()->GetBlock(index - 1)->CheckNearBlocks();
				}
			}

			//아래
			if (index + WIDTH < WIDTH * HEIGHT)
			{
				if (MineSweeper::GetInstance()->GetBlock(index + WIDTH)->state == BLOCK_STATE::NONECLICK)
				{
					MineSweeper::GetInstance()->GetBlock(index + WIDTH)->CheckNearBlocks();
				}
			}

			//위
			if (index - WIDTH >= 0)
			{
				if (MineSweeper::GetInstance()->GetBlock(index - WIDTH)->state == BLOCK_STATE::NONECLICK)
				{
					MineSweeper::GetInstance()->GetBlock(index - WIDTH)->CheckNearBlocks();
				}
			}

			//위-뒤
			if (index - WIDTH - 1 >= 0 && (index - WIDTH - 1) % WIDTH != WIDTH - 1)
			{
				if (MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->state == BLOCK_STATE::NONECLICK)
				{
					MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->CheckNearBlocks();
				}
			}

			//위-앞
			if (index - WIDTH + 1 > 0 && (index - WIDTH + 1) % WIDTH != 0)
			{
				if (MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->state == BLOCK_STATE::NONECLICK)
				{
					MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->CheckNearBlocks();
				}
			}

			//아래-앞
			if (index + WIDTH + 1 < WIDTH * HEIGHT && (index + WIDTH + 1) % WIDTH != 0)
			{
				if (MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->state == BLOCK_STATE::NONECLICK)
				{
					MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->CheckNearBlocks();
				}
			}

			//아래-뒤
			if (index + WIDTH - 1 < WIDTH * HEIGHT && (index + WIDTH - 1) % WIDTH != WIDTH - 1)
			{
				if (MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->state == BLOCK_STATE::NONECLICK)
				{
					MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->CheckNearBlocks();
				}
			}
		}
	}
}

void Block::ButtonUp()
{
	//앞
	if (index + 1 < WIDTH * HEIGHT && (index + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + 1)->tempOpen 
			&& MineSweeper::GetInstance()->GetBlock(index + 1)->state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index + 1)->SetState(BLOCK_STATE::NONECLICK);
		}
	}

	//뒤
	if (index - 1 >= 0 && (index - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - 1)->tempOpen
			&& MineSweeper::GetInstance()->GetBlock(index - 1)->state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index - 1)->SetState(BLOCK_STATE::NONECLICK);
		}
	}

	//아래
	if (index + WIDTH < WIDTH * HEIGHT
		&& MineSweeper::GetInstance()->GetBlock(index + WIDTH)->state == BLOCK_STATE::CLICKED)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH)->tempOpen)
		{
			MineSweeper::GetInstance()->GetBlock(index + WIDTH)->SetState(BLOCK_STATE::NONECLICK);
		}
	}

	//위
	if (index - WIDTH >= 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH)->tempOpen
			&& MineSweeper::GetInstance()->GetBlock(index - WIDTH)->state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index - WIDTH)->SetState(BLOCK_STATE::NONECLICK);
		}
	}

	//위-뒤
	if (index - WIDTH - 1 >= 0 && (index - WIDTH - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->tempOpen
			&& MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index - WIDTH - 1)->SetState(BLOCK_STATE::NONECLICK);
		}
	}

	//위-앞
	if (index - WIDTH + 1 > 0 && (index - WIDTH + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->tempOpen
			&& MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index - WIDTH + 1)->SetState(BLOCK_STATE::NONECLICK);
		}
	}

	//아래-앞
	if (index + WIDTH + 1 < WIDTH * HEIGHT && (index + WIDTH + 1) % WIDTH != 0)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->tempOpen
			&& MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index + WIDTH + 1)->SetState(BLOCK_STATE::NONECLICK);
		}
	}

	//아래-뒤
	if (index + WIDTH - 1 < WIDTH * HEIGHT && (index + WIDTH - 1) % WIDTH != WIDTH - 1)
	{
		if (MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->tempOpen
			&& MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->state == BLOCK_STATE::CLICKED)
		{
			MineSweeper::GetInstance()->GetBlock(index + WIDTH - 1)->SetState(BLOCK_STATE::NONECLICK);
		}
	}
}

bool Block::IsTempOpen()
{
	if (tempOpen)
		return true;
	else
		return false;
}

void Block::SetHasMine(bool _hasMine)
{
	hasMine = _hasMine;
}

bool Block::GetHasMine()
{
	return hasMine;
}

bool Block::GetIsOpen()
{
	return isOpen;
}

BLOCK_STATE Block::GetState()
{
	return state;
}

CLICK_STATE Block::CheckClick(POINT pt, int clickButton)
{
	if (pt.x > position.x && pt.x < position.x + size.cx && pt.y > position.y && pt.y < position.y + size.cy)
	{
		if (clickButton == 1 && (state == BLOCK_STATE::FLAG || state == BLOCK_STATE::NONECLICK))
		{
			if (state != BLOCK_STATE::FLAG)
			{
				SetState(BLOCK_STATE::FLAG);
				MineSweeper::GetInstance()->PlusFlagNum();
				return CLICK_STATE::BLOCK_CLICK;
			}
			else
			{
				SetState(BLOCK_STATE::NONECLICK);
				MineSweeper::GetInstance()->MinusFlagNum();
				return CLICK_STATE::BLOCK_CLICK;
			}	
		}
		else if (hasMine && clickButton == 0)
		{
			SetState(BLOCK_STATE::MINE);
			return CLICK_STATE::MINE_CLICK;
		}
		else if (!hasMine && clickButton == 0 && isOpen)
		{
			ClickNear();
			ClickOpenBlock = true;
			return CLICK_STATE::BLOCK_CLICK;
		}
		else if(!hasMine && clickButton == 0)
		{
			
			CheckNearBlocks();
			return CLICK_STATE::BLOCK_CLICK;
		}
	}

	if (clickButton == 2 && ClickOpenBlock)
	{
		ButtonUp();
	}
	return CLICK_STATE::NONE_BLOCK_CLICK;
}
