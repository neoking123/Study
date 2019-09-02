#include "MineSweeper.h"
#include "BlockManager.h"
#include "BitMapManager.h"
#include "Block.h"
#include "Macro.h"

BlockManager* BlockManager::pInstance = nullptr;

BlockManager::BlockManager()
{
}

BlockManager::~BlockManager()
{
}

void BlockManager::Init(int width, int height)
{
	size.cx = width;
	size.cy = height;

	for (int i = 0; i < size.cy; i++)
	{
		for (int j = 0; j < size.cx; j++)
		{
			Block* newBlock = new Block();
			newBlock->Init(j * BitMapManager::GetInstance()->GetBitMap(0)->GetSize().cx + 43, i * BitMapManager::GetInstance()->GetBitMap(0)->GetSize().cy + 45, BLOCK_STATE::NONECLICK);
			Blocks.push_back(newBlock);
		}
	}

	RandomSpawnMine();
}

Block * BlockManager::GetBlock(int index)
{
	if (Blocks[index])
	{
		return Blocks[index];
	}
	else
		return nullptr;
}

CLICK_STATE BlockManager::Input(POINT pt)
{
	CLICK_STATE isClickMine = CLICK_STATE::NONE_BLOCK_CLICK;
	for (auto iter = Blocks.begin(); iter != Blocks.end(); iter++)
	{
		isClickMine = (*iter)->CheckClick(pt);

		if (isClickMine == CLICK_STATE::MINE_CLICK)
		{
			return isClickMine;
		}
	}
	
	return isClickMine;
}

void BlockManager::Draw(HDC hdc)
{
	for (auto iter = Blocks.begin(); iter != Blocks.end(); iter++)
	{
		(*iter)->Draw(hdc);
	}
}

void BlockManager::Release()
{
	for (auto iter = Blocks.begin(); iter != Blocks.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}

void BlockManager::SpawnMine(int x, int y)
{
	Blocks[x + size.cx * y]->SetHasMine(true);
}

void BlockManager::RandomSpawnMine()
{
	int count = 0;
	int num = rand() % 100 + 10;
	int randomX;
	int randomY;

	while (num > count++)
	{
		randomX = rand() % MineSweeper::GetInstance()->GetSize().cx;
		randomY = rand() % MineSweeper::GetInstance()->GetSize().cy;
		SpawnMine(randomX, randomY);
	}
}
