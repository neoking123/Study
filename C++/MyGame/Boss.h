#pragma once
#include "Monster.h"

class Boss : public Monster
{
public:

	Boss();
	~Boss();

	virtual void Init(string name, int hp, int atk, int def, int rewardExp, Map* map);
};

