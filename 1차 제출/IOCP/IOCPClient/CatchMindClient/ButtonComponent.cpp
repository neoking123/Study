#include "ButtonComponent.h"
#include "BitMapManager.h"
#include "UIObject.h"
#include "Room.h"

bool ButtonComponent::CheckIsCliked(UIObject& uiObject, int x, int y)
{
	bool clickResult = false;
	if (uiObject.tag == "room")
	{
		Room& room = dynamic_cast<Room&>(uiObject);

		if (x > (room.roomAlignCount % 2) * ROOM_WIDTH + ROOM_MARGINE_WIDTH && x < (room.roomAlignCount % 2) * ROOM_WIDTH + ROOM_MARGINE_WIDTH + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_FRAME)->GetSize().cx
			&& y >(room.roomAlignCount / 2) * ROOM_HEIGHT + ROOM_MARGINE_HEIGHT && y < (room.roomAlignCount / 2) * ROOM_HEIGHT + ROOM_MARGINE_HEIGHT + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_ROOM_FRAME)->GetSize().cy)
		{
			clickResult = true;
		}
		else
			clickResult = false;
	}

	return clickResult;
}
