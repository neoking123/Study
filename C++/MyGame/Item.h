#pragma once
#include "Player.h"

enum EItemType
{
	HPPOTION,
	MPPOTION
};

class Item
{
private:
	EItemType itemType;
	int num;
	int value;

public:
	Item();
	~Item();

	void UseItem(Player& player);
	int GetNum();
	void SetNum(int num);
};

