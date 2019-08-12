#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Map& map)
{
	x = WIDTH / 2;
	y = HEIGHT / 2;
	map.aMap[y][x] = mapState::PLAYER;
}

void Player::input(Map& map)
{
	char input = _getch();

	if (input == 'w' && map.aMap[y - 1][x] != mapState::WALL)
	{
		y--;
		map.aMap[y - 1][x] == mapState::PLAYER;
		map.aMap[y][x] == mapState::EMPTY;
	}
	else if (input == 's' && map.aMap[y + 1][x] != mapState::WALL)
	{
		y++;
		map.aMap[y + 1][x] == mapState::PLAYER;
		map.aMap[y][x] == mapState::EMPTY;
	}
	else if (input == 'a' && map.aMap[y][x - 1] != mapState::WALL)
	{
		x--;
		map.aMap[y][x - 1] == mapState::PLAYER;
		map.aMap[y][x] == mapState::EMPTY;
	}
	else if (input == 'd' && map.aMap[y][x + 1] != mapState::WALL)
	{
		x++;
		map.aMap[y][x + 1] == mapState::PLAYER;
		map.aMap[y][x] == mapState::EMPTY;
	}
}
