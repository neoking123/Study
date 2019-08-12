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

// �� �ʱ�ȭ
void Map::Init()
{
	
}

// �� �׸���
void Map::Draw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (arrMap[y][x] == PLAYER)
			{
				cout << "��";
			}
			else if (arrMap[y][x] == WALL)
			{
				cout << "��";
			}
			else if (arrMap[y][x] == EMPTY)
			{
				cout << "  ";
			}
		}

		cout << endl;
	}
}