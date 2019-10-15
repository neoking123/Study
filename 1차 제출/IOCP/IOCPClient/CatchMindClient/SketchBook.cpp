#include "SketchBook.h"
#include "BitMapManager.h"
#include "LobbyManager.h"
#include "CatchMind.h"

SketchBook* SketchBook::instance = nullptr;
std::mutex SketchBook::mutex;

SketchBook::SketchBook()
{
}

void SketchBook::DrawSketchBook(HDC hdc)
{
	if (mouseTrack.size() > 0)
	{
		for (auto iter = mouseTrack.begin(); iter != mouseTrack.end(); iter++)
		{
			if ((*iter) == nullptr)
				return;

			if ((*iter)->isClickUp == true)
			{
				continue;
			}
			else
			{
				if (iter + 1 != mouseTrack.end())
				{
					MoveToEx(hdc, (*iter)->pos.x, (*iter)->pos.y, NULL);
					
					HPEN MyPen;
					HPEN OldPen;
					MyPen = CreatePen(PS_SOLID, (*iter)->thickness, RGB((*iter)->color.r, (*iter)->color.g, (*iter)->color.b));
					OldPen = (HPEN)SelectObject(hdc, MyPen);

					iter++;
					LineTo(hdc, (*iter)->pos.x, (*iter)->pos.y);
					iter--;

					SelectObject(hdc, OldPen);
					DeleteObject(MyPen);
				}
				else
				{
					MoveToEx(hdc, (*iter)->pos.x, (*iter)->pos.y, NULL);

					HPEN MyPen;
					HPEN OldPen;
					MyPen = CreatePen(PS_SOLID, (*iter)->thickness, RGB((*iter)->color.r, (*iter)->color.g, (*iter)->color.b));
					OldPen = (HPEN)SelectObject(hdc, MyPen);

					LineTo(hdc, (*iter)->pos.x, (*iter)->pos.y);

					SelectObject(hdc, OldPen);
					DeleteObject(MyPen);
					break;
				}
			}
		}
	}
}

void SketchBook::LClickDown(int x, int y)
{
	if (x < bitmap->GetSize().cx + 330 && x > 370
		&& y < bitmap->GetSize().cy + 130 && y > 150)
	{
		isClicked = true;
		BRUSH_DATA brush;
		brush.pos = { x, y };
		brush.color = curColor;
		brush.thickness = curThick;
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
		NetworkManager::GetInstance()->SendDrawToServer(roomNum, brush);

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
	curThick = 5;
	//mouseTrack.reserve(5000);
}

void SketchBook::Release()
{
	for (auto iter = mouseTrack.begin(); iter != mouseTrack.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	mouseTrack.clear();
}

void SketchBook::Render(HDC hdc)
{
	bitmap->Draw(hdc, 351, 140);
	DrawSketchBook(hdc);
	mutex.unlock();
}

void SketchBook::MouseInput(int x, int y, int mouseState)
{
	if (CatchMind::GetInstance()->GetSceneState() == SCENE_STATE::INGAME_SCENE)
	{
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
		if (LobbyManager::GetInstance()->GetCurrentTurn(roomNum) != CatchMind::GetInstance()->playerIndex)
			return;
	}

	if (mouseState == MOUSE_STATE::LCLICK_DOWN)
	{
		LClickDown(x, y);
	}
	else if (mouseState == MOUSE_STATE::RCLICK_DOWN)
	{
		RClickDown(x, y);
	}
	else if (mouseState == MOUSE_STATE::LCLICK_UP || mouseState == MOUSE_STATE::RCLICK_UP)
	{
		ClickUp(x, y);
	}
}

void SketchBook::DrawToSketchBook(int x, int y)
{
	if (x < bitmap->GetSize().cx + 330 && x > 370
		&& y < bitmap->GetSize().cy + 130 && y > 150)
	{
		BRUSH_DATA brush;
		brush.pos = { x, y };
		brush.color = curColor;
		brush.thickness = curThick;
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
		NetworkManager::GetInstance()->SendDrawToServer(roomNum, brush);
	}
}

void SketchBook::ClickUp(int x, int y)
{
	if (x < bitmap->GetSize().cx + 330 && x > 370
		&& y < bitmap->GetSize().cy + 130 && y > 150)
	{
		isClicked = false;
		BRUSH_DATA brush;
		brush.pos = { x, y };
		brush.isClickUp = true;
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
		NetworkManager::GetInstance()->SendDrawToServer(roomNum, brush);
	}
	else
	{
		isClicked = false;
		if (!mouseTrack.empty())
		{
			BRUSH_DATA brush;
			brush.pos = { mouseTrack.back()->pos.x, mouseTrack.back()->pos.y };
			brush.isClickUp = true;
			int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
			NetworkManager::GetInstance()->SendDrawToServer(roomNum, brush);
		}
	}
	curThick = 5;
}

void SketchBook::RClickDown(int x, int y)
{
	if (x < bitmap->GetSize().cx + 330 && x > 370
		&& y < bitmap->GetSize().cy + 130 && y > 150)
	{
		isClicked = true;
		BRUSH_DATA brush;
		brush.pos = { x, y };
		brush.color = curColor;
		curThick = 30;
		brush.thickness = curThick;
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
		NetworkManager::GetInstance()->SendDrawToServer(roomNum, brush);
	}
}

void SketchBook::PushBackSketchBook(BRUSH_DATA brushData)
{
	BRUSH_DATA* newBrush = new BRUSH_DATA;
	newBrush->pos = brushData.pos;
	newBrush->color = brushData.color;
	newBrush->thickness = brushData.thickness;
	newBrush->isClickUp = brushData.isClickUp;
	mouseTrack.push_back(newBrush);

	mutex.unlock();
}

void SketchBook::SetSketchBook(BRUSH_DATA * brushData, int len)
{
	for (int i = 0; i < len; i++)
	{
		BRUSH_DATA* newBrush = new BRUSH_DATA;
		newBrush->pos = brushData[i].pos;
		newBrush->color = brushData[i].color;
		newBrush->thickness = brushData[i].thickness;
		newBrush->isClickUp = brushData[i].isClickUp;
		mouseTrack.push_back(newBrush);
	}

	mutex.unlock();
}

void SketchBook::CleanSketchBook()
{
	for (auto iter = mouseTrack.begin(); iter != mouseTrack.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	mouseTrack.clear();
}

void SketchBook::SetColor(RGB color)
{
	curColor = color;
}
