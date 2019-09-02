#include "CardGame.h"
#include "BitMapManager.h"
#include "BitMap.h"
#include "Card.h"
#include <algorithm>
#include "Macro.h"

CardGame* CardGame::pInstance = nullptr;

CardGame::CardGame()
{
}


CardGame::~CardGame()
{
}

void CardGame::Init(HWND hWnd, HDC hdc, HINSTANCE hInst)
{
	srand(GetTickCount());
	this->hWnd = hWnd;
	BitMapManager::GetInstance()->Init(hdc, hInst);
	Cards.reserve(20);

	int iArray[20];

	for (int i = 0; i < 20; i++)
		iArray[i] = i % 10;

	for (int i = 0; i < 500; i++)
	{
		int randA = rand() % 20;
		int randB = rand() % 20;

		int iTemp = iArray[randA];
		iArray[randA] = iArray[randB];
		iArray[randB] = iTemp;
	}

	for (int i = 0; i < 20; i++)
	{
		Card* newCard = new Card();
		newCard->Init(BitMapManager::GetInstance()->GetBitMap(iArray[i]), BitMapManager::GetInstance()->GetBitMap(CARD_LIST::BACK), (i % 10) * WIDTH, (i / 10) * HEIGHT, iArray[i]);
		Cards.push_back(newCard);
	}

}

void CardGame::Update()
{
}

void CardGame::Draw(HDC hdc)
{
	for (auto iter = Cards.begin(); iter != Cards.end(); iter++)
	{
		(*iter)->Draw(hdc);
	}
}

void CardGame::Release()
{
	for (auto iter = Cards.begin(); iter != Cards.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}
