#include "Item.h"

Item::Item()
{
	num = 0;
	value = 10;
}

Item::~Item()
{
}

void Item::UseItem(Player& player)
{
	if (itemType == EItemType::HPPOTION)
	{
		player.SetHp(player.GetHp() + value);
	}
	else if (itemType == EItemType::MPPOTION)
	{
		player.SetMp(player.GetMp() + value);
	}
}

int Item::GetNum()
{
	return num;
}

void Item::SetNum(int num)
{
	this->num = num;
}
