#include "Monster.h"
#include "Player.h"

Monster::Monster()
{
	name = "";
	hp = 0;
	atk = 0;
	def = 0;
	rewardExp = 0;
	position = nullptr;
}

void Monster::Init(string name, int hp, int atk, int def, int rewardExp, Map* map)
{
	this->name = name;
	this->hp = hp;
	this->atk = atk;
	this->def = def;
	this->rewardExp = rewardExp;
	this->currentMap = map;

	position = currentMap->GetPosition(12, 5);
	position->bMonster = true;
}

Monster::~Monster()
{
}

int Monster::Attack(Player & player)
{
	int acc = rand() % player.def - (atk - player.def);
	int damage = atk - player.def + acc;
	player.hp -= damage;

	return damage;
}
