#include "Player.h"

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

void Player::Init(int hp, int mp, int atk, int def, int exp, int level, Map* map)
{
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

int Player::GetHp()
{
	return hp;
}

int Player::GetMp()
{
	return mp;
}

void Player::SetHp(int newHp)
{
	hp = newHp;
}

void Player::SetMp(int newMp)
{
	mp = newMp;
}

void Player::Input()
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
	else if (input == EKey::CONFIRM)
	{

	}
	else if (input == EKey::CANCLE)
	{

	}
}

void Player::ChangeMap(Map * map, EMap currentMapName)
{
	currentMap = map;
	this->currentMapName = currentMapName;
}
