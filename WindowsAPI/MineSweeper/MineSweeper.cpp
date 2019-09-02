#include "MineSweeper.h"
#include "BitMapManager.h"
#include "BlockManager.h"
#include "Block.h"

MineSweeper* MineSweeper::pInstance = nullptr;

MineSweeper::MineSweeper()
{
}


MineSweeper::~MineSweeper()
{
}

void MineSweeper::Init(HDC hdc, HINSTANCE hInst, HWND hWnd)
{
	size.cx = WIDTH;
	size.cy = HEIGHT;
	BitMapManager::GetInstance()->Init(hdc, hInst);
	BlockManager::GetInstance()->Init(size.cx, size.cy);
	this->hWnd = hWnd;
}

void MineSweeper::Release()
{
	
}

void MineSweeper::Draw(HDC hdc)
{
	DrawBackground(hdc);
	BlockManager::GetInstance()->Draw(hdc);
}

void MineSweeper::Update()
{
}

void MineSweeper::Input(POINT pt)
{
	CLICK_STATE isClickedMine = CLICK_STATE::NONE_BLOCK_CLICK;
	isClickedMine = BlockManager::GetInstance()->Input(pt);

	if (isClickedMine == CLICK_STATE::MINE_CLICK)
	{
		SendGamOverMessage();
	}
	
}

void MineSweeper::DrawBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::RES_12)->Draw(hdc, 0, 0);
}

void MineSweeper::SendGamOverMessage()
{
	MessageBox(hWnd, TEXT("지뢰를 밟았습니다.. 으악!"), TEXT("게임 종료"), MB_OK);
	//SendMessage(hWnd, WM_DESTROY, 1, 0);
}

SIZE MineSweeper::GetSize()
{
	return size;
}
