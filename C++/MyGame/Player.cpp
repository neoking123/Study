#include "Player.h"
#include "Monster.h"

Player::Player()
{
	hp = 0;
	mp = 0;
	atk = 0;
	def = 0;
	exp = 0;
	level = 0;
}

Player::~Player()
{
}

void Player::Init(string name, int hp, int mp, int atk, int def, int exp, int level, Map* map)
{
	this->name = name;
	this->hp = hp;
	this->mp = mp;
	this->atk = atk;
	this->def = def;
	this->exp = exp;
	this->level = level;
	this->currentMap = map;

	currentMapName = EMap::VILLAGE;

	position = this->currentMap->GetPosition(map->GetMapWidth() / 2 + 1, map->GetMapHeight() / 2 + 5);
	position->bPlayer = true;
}

string Player::GetName()
{
	return name;
}

int Player::GetHp()
{
	return hp;
}

int Player::GetMp()
{
	return mp;
}

int Player::GetAtk()
{
	return atk;
}

int Player::GetDef()
{
	return def;
}

int Player::GetExp()
{
	return exp;
}

int Player::GetLevel()
{
	return level;
}

void Player::SetHp(int newHp)
{
	hp = newHp;
}

void Player::SetMp(int newMp)
{
	mp = newMp;
}

EKey Player::Input()
{
	char input = _getch();

	if (input == EKey::UP 
		&& currentMap->GetMapState(position->x, position->y - 1) != EMapState::WALL
		&& currentMap->GetMapState(position->x, position->y - 1) != EMapState::BRICK
		&& currentMap->GetMapState(position->x, position->y - 1) != EMapState::LOOF)
	{
		position->bPlayer = false;
		position = currentMap->GetPosition(position->x, position->y - 1);
		position->bPlayer = true;
	}
	else if (input == EKey::DOWN
		&& currentMap->GetMapState(position->x, position->y + 1) != EMapState::WALL
		&& currentMap->GetMapState(position->x, position->y + 1) != EMapState::BRICK
		&& currentMap->GetMapState(position->x, position->y + 1) != EMapState::LOOF)
		
	{
		position->bPlayer = false;
		position = currentMap->GetPosition(position->x, position->y + 1);
		position->bPlayer = true;
	}
	else if (input == EKey::LEFT
		&& currentMap->GetMapState(position->x - 1, position->y) != EMapState::WALL
		&& currentMap->GetMapState(position->x - 1, position->y) != EMapState::BRICK
		&& currentMap->GetMapState(position->x - 1, position->y) != EMapState::LOOF)
	{
		position->bPlayer = false;
		position = currentMap->GetPosition(position->x - 1, position->y);
		position->bPlayer = true;
	}
	else if (input == EKey::RIGHT
		&& currentMap->GetMapState(position->x + 1, position->y) != EMapState::WALL
		&& currentMap->GetMapState(position->x + 1, position->y) != EMapState::BRICK
		&& currentMap->GetMapState(position->x + 1, position->y) != EMapState::LOOF)
	{
		position->bPlayer = false;
		position = currentMap->GetPosition(position->x + 1, position->y);
		position->bPlayer = true;
	}
	else if (input == EKey::CONFIRM) // 'x'Ű
	{

	}
	else if (input == EKey::CANCLE) // 'z'Ű
	{

	}

	return (EKey)input;
}

void Player::ChangeMap(Map * map, EMap currentMapName)
{
	currentMap = map;
	this->currentMapName = currentMapName;
}

int Player::Attack(Monster & monster)
{
	int acc = rand() % monster.def - (atk - monster.def);
	int damage = atk - monster.def + acc;
	monster.hp -= damage;

	return damage;
}

int Player::MagicAttck(Monster & monster)
{
	if (mp >= 25)
	{
		int acc = rand() % 10 - 10;
		int damage = 15 + acc;
		monster.hp -= damage;

		return damage;
	}
	return 0;
}
