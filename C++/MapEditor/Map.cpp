#include "Map.h"

Map::Map()
{
	mapWidth = 0;
	mapHeight = 0;
	cursor = nullptr;
}

Map::~Map()
{

}

void Map::Init(int width, int height)
{
	mapWidth = width;
	mapHeight = height;

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			Position* newPosion = new Position(j, i);
			map.push_back(newPosion);
		}
	}

	// 커서 초기 위치
	cursor = map[(mapWidth / 2) + mapWidth * (mapHeight / 2)];
	//cursor->mapState = CURSOR;
}

void Map::Draw()
{
	system("cls");
	for (int i = 0; i < mapHeight * mapWidth; i += mapWidth)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (map[i + j]->bCursor)
			{
				cout << "★";
			}
			else if (map[i + j]->mapState == EMPTY)
			{	
				cout << "□";
			}
			else if (map[i + j]->mapState == WALL)
			{
				cout << "■";
			}
			else if (map[i + j]->mapState == LOOF)
			{
				cout << "▲";
			}
			else if (map[i + j]->mapState == BRICK)
			{
				cout << "▧";
			}
			else if (map[i + j]->mapState == PLAYER)
			{
				cout << "☆";
			}
			else if (map[i + j]->mapState == MONSTER)
			{
				cout << "♤";
			}
			else if (map[i + j]->mapState == BOSS)
			{
				cout << "♧";
			}
		}
		cout << endl;
	}
}

void Map::PrintMenu()
{
	cout << endl;
	cout << endl;
	cout << "w : 위, s : 아래, a : 왼쪽, d : 오른쪽, o : 저장, p : 종료" << endl;
	cout << "1 : 지우기, 2 : 벽, 3 : 지붕, 4 : 블록" << endl;
}

void Map::CreateCursor()
{
	cursor->bCursor = true;
}

char Map::InputCursor()
{
	char input = _getch();
	
	if (input == 'w' && cursor->y > 0)
	{
		cursor->bCursor = false;
		cursor = map[(cursor->x + mapWidth * cursor->y) - mapWidth];
		cursor->bCursor = true;
	}
	else if (input == 's' && cursor->y < mapHeight - 1)
	{
		cursor->bCursor = false;
		cursor = map[(cursor->x + mapWidth * cursor->y) + mapWidth];
		cursor->bCursor = true;
	}
	else if (input == 'a' && cursor->x > 0)
	{
		cursor->bCursor = false;
		cursor = map[(cursor->x + mapWidth * cursor->y) - 1];
		cursor->bCursor = true;
	}
	else if (input == 'd' && cursor->x < mapWidth - 1)
	{
		cursor->bCursor = false;
		cursor = map[(cursor->x + mapWidth * cursor->y) + 1];
		cursor->bCursor = true;
	}
	else if (input == '1')
	{
		cursor->mapState = EMPTY;
	}
	else if (input == '2')
	{
		cursor->mapState = WALL;
	}
	else if (input == '3')
	{
		cursor->mapState = LOOF;
	}
	else if (input == '4')
	{
		cursor->mapState = BRICK;
	}

	return input;
}

void Map::EditMap(int x, int y, EMapState mapState)
{
	map[y][x].mapState = mapState;
}

EMapState Map::GetMapState(int x, int y)
{
	return map[x + mapWidth * y]->mapState;
}