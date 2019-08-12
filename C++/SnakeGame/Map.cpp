#include "Map.h"

Map::Map()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			arrMap[y][x] = mapState::EMPTY;
		}
	}
}

Map::~Map()
{
}

// ¸Ê ÃÊ±âÈ­
void Map::Init()
{
	
}

// ¸Ê ±×¸®±â
void Map::Draw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (arrMap[y][x] == PLAYER)
			{
				cout << "¡Ù";
			}
			else if (arrMap[y][x] == WALL)
			{
				cout << "¢É";
			}
			else if (arrMap[y][x] == EMPTY)
			{
				cout << "  ";
			}
		}

		cout << endl;
	}
}