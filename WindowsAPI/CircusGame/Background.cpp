#include "Background.h"
#include "BitMapManager.h"
#include "Sprite.h"
#include "Camera.h"


Background::Background()
{
}


Background::~Background()
{
}

void Background::Init()
{
	BackgroundObjects.reserve(10);
	Sprite sprite;

	for (int i = 0; i < 4; i++)
	{
		
		sprite.Init(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK + i));
		BackgroundObjects.push_back(sprite);
	}

	sprite.Init(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MITER));
	BackgroundObjects.push_back(sprite);
	sprite.Init(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::GOAL));
	BackgroundObjects.push_back(sprite);
}

void Background::Update(HDC gameDC, Camera& camera)
{
	for (int i = 0; i < 100; i++)
	{
		/*if (BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cx * i < camera.transform.position.x + camera.GetSize().cx)
		{
			BackgroundObjects[0].Draw(gameDC, BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cx * i, 330);
			BackgroundObjects[2].Draw(gameDC, BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_NORMAL)->GetSize().cx * i, 250);
			
			if (BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cx * i % 7 == 0)
			{
				BackgroundObjects[1].Draw(gameDC, BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->GetSize().cx * i, 250);
			}
		}*/

		if (BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cx * i < camera.transform.position.x + camera.GetSize().cx)
		{
			BackgroundObjects[0].Draw(gameDC, BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cx * i, 330);
			BackgroundObjects[2].Draw(gameDC, BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_NORMAL)->GetSize().cx * i, 250);

			
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cx * i < camera.transform.position.x + camera.GetSize().cx)
		{
			if (BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cx * i % 7 == 0)
			{
				BackgroundObjects[1].Draw(gameDC, BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->GetSize().cx * (i + 3), 250);
				BackgroundObjects[4].Draw(gameDC, BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->GetSize().cx * (i + 1), 560);
				DrawMiterCount(gameDC, 100 - (i / 7 * 10), BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->GetSize().cx * (i + 1) + 25, 560 + 5);

				if (100 - (i / 7 * 10) == 0)
				{
					BackgroundObjects[5].Draw(gameDC, BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->GetSize().cx * (i + 1), 500);
				}
			}
		}
	}
}

void Background::DrawMiterCount(HDC gameDC, int miter, int x, int y)
{
	string s = to_string(miter);

	SetBkColor(gameDC, RGB(0, 0, 0));
	HFONT myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "±Ã¼­Ã¼");
	HFONT oldFont = (HFONT)SelectObject(gameDC, myFont);
	SetTextColor(gameDC, RGB(255, 255, 255));

	TextOut(gameDC, x, y, s.c_str(), s.length());

	SetTextColor(gameDC, RGB(0, 0, 0));
	SelectObject(gameDC, oldFont);
	SetBkColor(gameDC, RGB(255, 255, 255));
	DeleteObject(myFont);
}