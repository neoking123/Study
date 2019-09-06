#include "SceneManager.h"
#include "SceneObject.h"
#include "BitMapManager.h"

SceneManager* SceneManager::pInstance = nullptr;

SceneManager::SceneManager()
{
}

void SceneManager::DrawBackground(HDC hdc)
{
	int backWidth = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cx;
	int backHeight = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->GetSize().cy;

	int decoWidth = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->GetSize().cx;
	int decoHeight = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->GetSize().cy;

	int normalHeight = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_NORMAL)->GetSize().cy;

	// Background
	for (int i = 0; i < 100; i++)
	{
		int currentDrawPoint = - posX + i * (backWidth - 1);
		if (currentDrawPoint > - 200 && currentDrawPoint < sceneSize.cx)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->Draw(hdc, - posX + i * (backWidth - 1), 193);
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_NORMAL)->Draw(hdc, - posX + i * (backWidth - 1), normalHeight * 2);
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_BOTTOM)->Draw(hdc, - posX + i * (backWidth - 1), 193 + backHeight);
		}
	}

	// Back_Deco, Miter
	for (int i = 0; i < 100; i++)
	{
		int currentDrawPoint = - posX + i * decoWidth;
		if (currentDrawPoint > - 200 && currentDrawPoint < sceneSize.cx)
		{
			if (i % 8 == 0)
			{
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->Draw(hdc, - posX + i * decoWidth + backWidth * 2, decoHeight * 2 - 8);
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MITER)->Draw(hdc, -posX + i * decoWidth + 20, 193 + backHeight + 5);
				DrawMiterCount(100 - (i / 8 * 10), -posX + i * decoWidth + 45, 193 + backHeight + 10);
				
				if (100 - (i / 8 * 10) == 0)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::GOAL)->Draw(hdc, -posX + i * decoWidth, 140 + backHeight);
				}
			}
		}
	}

}

void SceneManager::DrawMiterCount(int miter, int x, int y)
{
	string s = to_string(miter);

	SetBkColor(sceneHDC, RGB(0, 0, 0));
	HFONT myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "±Ã¼­Ã¼");
	HFONT oldFont = (HFONT)SelectObject(sceneHDC, myFont);
	SetTextColor(sceneHDC, RGB(255, 255, 255));

	TextOut(sceneHDC, x, y, s.c_str(), s.length());

	SetTextColor(sceneHDC, RGB(0, 0, 0));
	SelectObject(sceneHDC, oldFont);
	SetBkColor(sceneHDC, RGB(255, 255, 255));
	DeleteObject(myFont);
}

void SceneManager::Draw_Debug(int value)
{
	string s = to_string(value);

	SetBkColor(sceneHDC, RGB(0, 0, 0));
	HFONT myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "±Ã¼­Ã¼");
	HFONT oldFont = (HFONT)SelectObject(sceneHDC, myFont);
	SetTextColor(sceneHDC, RGB(255, 255, 255));

	TextOut(sceneHDC, 100, 10, s.c_str(), s.length());

	SetTextColor(sceneHDC, RGB(0, 0, 0));
	SelectObject(sceneHDC, oldFont);
	SetBkColor(sceneHDC, RGB(255, 255, 255));
	DeleteObject(myFont);
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(HDC hdc, SIZE size)
{
	sceneSize = size;
	drawPointX = 0;
	posX = 0;
	sceneHDC = CreateCompatibleDC(hdc);
	hBitMap = CreateCompatibleBitmap(hdc, sceneSize.cx, sceneSize.cy);
	hOldBitMap = (HBITMAP)SelectObject(sceneHDC, hBitMap);

	// BitMapManager ÃÊ±âÈ­
	BitMapManager::GetInstance()->Init(sceneHDC);
}

void SceneManager::DrawScene(HDC hdc)
{
	Draw_Debug(posX);

	DrawBackground(sceneHDC);

	if (!sceneObjects.empty())
	{
		for (auto iter = sceneObjects.begin(); iter != sceneObjects.end(); iter++)
		{
			if ((*iter)->IsCharacter())
			{
				(*iter)->DrawFixedPosition(sceneHDC, 100);
			}
			else
			{
				(*iter)->Draw(sceneHDC);
			}
		}
	}

	BitBlt(hdc, 0, 0, sceneSize.cx, sceneSize.cy, sceneHDC, 0, 0, SRCCOPY);
}

void SceneManager::AddSceneObject(SceneObject* newObj)
{
	sceneObjects.push_back(newObj);
}

void SceneManager::Relese()
{
	SelectObject(sceneHDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(sceneHDC);
}

void SceneManager::Input(POINT pos)
{
	posX = pos.x - offset;
}

int SceneManager::GetObjectsNum()
{
	return sceneObjects.size();
}

void SceneManager::SetOffset(POINT pos)
{
	offset = pos.x - posX;
}
