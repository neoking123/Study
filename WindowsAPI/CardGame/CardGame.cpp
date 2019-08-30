#include "CardGame.h"
#include "BitMap.h"
#include "Card.h"

CardGame* CardGame::pInstance = nullptr;

CardGame::CardGame()
{
}


CardGame::~CardGame()
{
}

void CardGame::Init(HWND hWnd, HDC hdc, HINSTANCE hInst)
{
	this->hWnd = hWnd;
	//bitMap = new BitMap();
	//bitMap->Init(hdc, hInst, CARD_LIST::BACK);
}

void CardGame::Update()
{
}

void CardGame::Draw(HDC hdc)
{
	bitMap->Draw(hdc, hWnd,100, 100, WIDTH, HEIGHT);
}

void CardGame::Release()
{
}
