#include "Map.h"

Map::Map()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			aMap[y][x] = 0;
		}
	}
}

Map::~Map()
{
}

void Map::Init()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			aMap[y][x] = mapState::EMPTY;
		}
	}
}

void Map::Draw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (aMap[y][x] == PLAYER)
			{
				cout << "¡Ù";
			}
			else if (aMap[y][x] == WALL)
			{
				cout << "¢É";
			}
			else if (aMap[y][x] == EMPTY)
			{
				cout << "  ";
			}
			/*else if (aMap[y][x] == 2)
			{
				cout << "¢À";
			}
			else if (aMap[y][x] == 3)
			{
				cout << "¡Ü";
			}*/
		}

		cout << endl;
	}
}
