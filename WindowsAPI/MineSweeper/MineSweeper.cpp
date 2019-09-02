#include <string>
#include "MineSweeper.h"
#include "BitMapManager.h"
#include "Block.h"
#include "Macro.h"

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
	this->hWnd = hWnd;
	mineNum = 0;
	timer = 0;

	for (int i = 0; i < size.cy; i++)
	{
		for (int j = 0; j < size.cx; j++)
		{
			Block* newBlock = new Block();
			newBlock->Init(j * BitMapManager::GetInstance()->GetBitMap(0)->GetSize().cx + 43, i * BitMapManager::GetInstance()->GetBitMap(0)->GetSize().cy + 45, BLOCK_STATE::NONECLICK, j + size.cx * i);
			Blocks.push_back(newBlock);
		}
	}

	RandomSpawnMine();
}

void MineSweeper::Release()
{
	for (auto iter = Blocks.begin(); iter != Blocks.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}

void MineSweeper::Draw(HDC hdc)
{
	DrawBackground(hdc);
	DrawSmile(hdc);
	DrawMineCount(hdc);
	DrawTimer(hdc);
	

	for (auto iter = Blocks.begin(); iter != Blocks.end(); iter++)
	{
		(*iter)->Draw(hdc);
	}
}

void MineSweeper::Update()
{
	timer++;
}

void MineSweeper::Input(POINT pt, int clickButton)
{
	CLICK_STATE isClickedMine = CLICK_STATE::NONE_BLOCK_CLICK;

	for (auto iter = Blocks.begin(); iter != Blocks.end(); iter++)
	{
		isClickedMine = (*iter)->CheckClick(pt, clickButton);
		if (isClickedMine == CLICK_STATE::MINE_CLICK)
		{
			SendGamOverMessage();
			break;
		}
	}
}

void MineSweeper::DrawBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::RES_12)->Draw(hdc, 0, 0);
}

void MineSweeper::DrawMineCount(HDC hdc)
{
	string s = to_string(mineNum);
	SetBkColor(hdc, RGB(52, 92, 162));
	HFONT myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "±Ã¼­Ã¼");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));

	TextOut(hdc, 670, 480, s.c_str(), s.length());

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	SetBkColor(hdc, RGB(255, 255, 255));
	DeleteObject(myFont);
}

void MineSweeper::DrawTimer(HDC hdc)
{
	string s = to_string(timer);
	SetBkColor(hdc, RGB(52, 92, 162));
	HFONT myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "±Ã¼­Ã¼");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));

	TextOut(hdc, 180, 480, s.c_str(), s.length());

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	SetBkColor(hdc, RGB(255, 255, 255));
	DeleteObject(myFont);
}

void MineSweeper::DrawSmile(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::RES_13)->Draw(hdc, 400, 2);
}

void MineSweeper::SpawnMine(int x, int y)
{
	Blocks[x + size.cx * y]->SetHasMine(true);
}

void MineSweeper::RandomSpawnMine()
{
	int count = 0;
	//int num = rand() % 100 + 10;
	int num = 50;
	int randomX;
	int randomY;

	while (num > count++)
	{
		randomX = rand() % size.cx;
		randomY = rand() % size.cy;
		SpawnMine(randomX, randomY);
	}

	mineNum = num;
}

void MineSweeper::SendGamOverMessage()
{
	OpenAllMines();
	MessageBox(hWnd, TEXT("Áö·Ú¸¦ ¹â¾Ò½À´Ï´Ù.. À¸¾Ç!"), TEXT("°ÔÀÓ Á¾·á"), MB_OK);
	//SendMessage(hWnd, WM_DESTROY, 1, 0);
}

void MineSweeper::OpenAllMines()
{
	for (auto iter = Blocks.begin(); iter != Blocks.end(); iter++)
	{
		if ((*iter)->GetHasMine())
		{
			(*iter)->SetState(BLOCK_STATE::MINE);
		}
	}
}

SIZE MineSweeper::GetSize()
{
	return size;
}

Block * MineSweeper::GetBlock(int index)
{
	if (Blocks[index])
		return Blocks[index];
	else
		return nullptr;
}
