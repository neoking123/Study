#include "RoomCreateButton.h"
#include "BitMapManager.h"

void RoomCreateButton::CheckIsCliked(int x, int y)
{
	if (button.CheckIsCliked(*this, x, y))
	{

	}
}

RoomCreateButton::RoomCreateButton()
{
}

RoomCreateButton::~RoomCreateButton()
{
}

void RoomCreateButton::Init(int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
}

void RoomCreateButton::Update()
{
}

void RoomCreateButton::Render(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_BUTTON_CREATE)->Draw(hdc, transform.position.x, transform.position.y);
}

void RoomCreateButton::Release()
{
}
