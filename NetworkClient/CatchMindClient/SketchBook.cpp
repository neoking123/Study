#include "SketchBook.h"
#include "BitMapManager.h"

SketchBook* SketchBook::instance = nullptr;

SketchBook::SketchBook()
{
}

void SketchBook::DrawSketchBook(HDC hdc)
{
	if (mouseTrack.size() > 1)
	{
		for (auto iter = mouseTrack.begin(); iter != mouseTrack.end();)
		{
			if ((*iter)->isClickUp == true)
			{
				if (iter + 1 != mouseTrack.end())
				{
					iter++;
				}
				else
				{
					break;
				}
			}
			else
			{
				MoveToEx(hdc, (*iter)->pos.x, (*iter)->pos.y, NULL);
				if (iter + 1 != mouseTrack.end())
				{
					iter++;
					LineTo(hdc, (*iter)->pos.x, (*iter)->pos.y);
				}
				else
				{
					break;
				}
			}
		}
	}
}

SketchBook::~SketchBook()
{
}

void SketchBook::Init()
{
	bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::SKETCH_BOOK);
	isClicked = false;
	curColor = {0, 0, 0};
	curThick = 1;
}

void SketchBook::Render(HDC hdc)
{
	bitmap->Draw(hdc, 351, 140);
	DrawSketchBook(hdc);
}

void SketchBook::MouseInput(int x, int y, int mouseState)
{
	if (x < bitmap->GetSize().cx + 351 && x > 351
		&& y < bitmap->GetSize().cy + 140 && y > 140)
	{
		isClicked = true;
		BRUSH_INFO* brush = new BRUSH_INFO;
		brush->pos = { x, y };
		brush->color = curColor;
		brush->thickness = curThick;
		mouseTrack.push_back(brush);
	}
}

void SketchBook::DrawToSketchBook(int x, int y)
{
	BRUSH_INFO* brush = new BRUSH_INFO;
	brush->pos = { x, y };
	brush->color = curColor;
	brush->thickness = curThick;
	mouseTrack.push_back(brush);
}

void SketchBook::ClickUp(int x, int y)
{
	isClicked = false;
	BRUSH_INFO* brush = new BRUSH_INFO;
	brush->pos = { x, y };
	brush->isClickUp = true;
	mouseTrack.push_back(brush);
}
