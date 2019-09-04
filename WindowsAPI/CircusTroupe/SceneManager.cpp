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

	int normalWidth = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_NORMAL)->GetSize().cx;
	int normalHeight = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_NORMAL)->GetSize().cy;

	int bottomlWidth = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_BOTTOM)->GetSize().cx;
	int bottomHeight = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_BOTTOM)->GetSize().cy;

	for (int i = 0; i < 9; i++)
	{
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK)->Draw(hdc, drawPointX - posX + i * (backWidth - 1), 193);
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_NORMAL)->Draw(hdc, drawPointX - posX + i * (normalWidth - 1), normalHeight * 2);
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_BOTTOM)->Draw(hdc, drawPointX - posX + i * (bottomlWidth - 1), 193 + backHeight);
	}

	for (int i = 0; i < 9; i++)
	{
		if (i / 3 == 1 && i % 3 == 0)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_DECO)->Draw(hdc, drawPointX - posX + i * decoWidth, decoHeight * 2 - 8);
		}
	}

}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(HDC hdc, SIZE size)
{
	sceneSize = size;
	drawPointX = 0;
	posX = 0;
	SceneHDC = CreateCompatibleDC(hdc);
	hBitMap = CreateCompatibleBitmap(hdc, sceneSize.cx, sceneSize.cy);
	hOldBitMap = (HBITMAP)SelectObject(SceneHDC, hBitMap);

	// BitMapManager ÃÊ±âÈ­
	BitMapManager::GetInstance()->Init(SceneHDC);
}

void SceneManager::DrawScene(HDC hdc)
{
	DrawBackground(SceneHDC);

	if (!sceneObjects.empty())
	{
		for (auto iter = sceneObjects.begin(); iter != sceneObjects.end(); iter++)
		{
			if ((*iter)->IsCharacter())
			{
				(*iter)->DrawFixedPosition(SceneHDC, 100);
			}
			else
			{
				(*iter)->Draw(SceneHDC);
			}
		}
	}

	BitBlt(hdc, 0, 0, sceneSize.cx, sceneSize.cy, SceneHDC, 0, 0, SRCCOPY);
}

void SceneManager::CheckBoundary(POINT pos)
{
	if (posX > drawPointX)
	{
		//drawPointX = posX + sceneSize.cx;
	}
}

void SceneManager::AddSceneObject(SceneObject* newObj)
{
	sceneObjects.push_back(newObj);
}

void SceneManager::Relese()
{
	SelectObject(SceneHDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(SceneHDC);
}

void SceneManager::Input(POINT pos)
{
	posX = pos.x - offset;
	CheckBoundary(pos);
}

int SceneManager::GetObjectsNum()
{
	return sceneObjects.size();
}

void SceneManager::SetOffset(POINT pos)
{
	offset = pos.x - posX;
}
