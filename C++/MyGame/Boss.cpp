#include "Boss.h"

Boss::Boss()
{
}


Boss::~Boss()
{
}

void Boss::Init(string name, int hp, int atk, int def, int rewardExp, Map * map)
{
	//Monster::Init(name, hp, atk, def, rewardExp, map);
	this->name = name;
	this->hp = hp;
	this->atk = atk;
	this->def = def;
	this->rewardExp = rewardExp;
	this->currentMap = map;

	position = currentMap->GetPosition(30, 5);
	position->bBoss = true;
	position->bMonster = false;
}
