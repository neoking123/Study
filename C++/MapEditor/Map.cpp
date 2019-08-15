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

int Map::GetMapWidth()
{
	return mapWidth;
}

int Map::GetMapHeight()
{
	return mapHeight;
}

void Map::Draw()
{
	//system("cls");
	COORD Cur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

	for (int i = 0; i < mapHeight * mapWidth; i += mapWidth)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (map[i + j]->bCursor)
			{
				cout << "★";
			}
			else if (map[i + j]->bPlayer)
			{
				cout << "☆";
			}
			else if (map[i + j]->mapState == EMapState::EMPTY)
			{	
				cout << "  ";
			}
			else if (map[i + j]->mapState == EMapState::WALL)
			{
				cout << "■";
			}
			else if (map[i + j]->mapState == EMapState::LOOF)
			{
				cout << "▲";
			}
			else if (map[i + j]->mapState == EMapState::BRICK)
			{
				cout << "▧";
			}
			else if (map[i + j]->mapState == EMapState::PO_VIL_BA)
			{
				cout << "▒";
			}
			else if (map[i + j]->mapState == EMapState::PO_BA_VIL)
			{
				cout << "▒";
			}
			else if (map[i + j]->mapState == EMapState::PO_BA_BO)
			{
				cout << "♨";
			}
			else if (map[i + j]->mapState == EMapState::PO_BO_BA)
			{
				cout << "♨";
			}
			//else if (currentMap[i + j]->mapState == EMapState::PLAYER)
			//{
			//	cout << "☆";
			//}
			else if (map[i + j]->mapState == EMapState::MONSTER)
			{
				cout << "♤";
			}
			else if (map[i + j]->mapState == EMapState::BOSS)
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
	cout << "이동 : 방향키, w : 저장, q : 종료" << endl;
	cout << "Space : 지우기, 1 : 벽, 2 : 지붕, 3 : 블록" << endl;
	cout << "4 : 마을->사냥터 포탈, 5 : 사냥터->마을 포탈" << endl;
	cout << "5 : 사냥터->보스 포탈, 6 : 보스->사냥터 포탈" << endl;
}

void Map::CreateCursor()
{
	cursor->bCursor = true;
}

void Map::DeleteCursor()
{
	cursor->bCursor = false;
}

char Map::InputCursor()
{
	char input = _getch();
	
	if (input == EKey::UP && cursor->y > 0)
	{
		cursor->bCursor = false;
		cursor = map[(cursor->x + mapWidth * cursor->y) - mapWidth];
		cursor->bCursor = true;
	}
	else if (input == EKey::DOWN && cursor->y < mapHeight - 1)
	{
		cursor->bCursor = false;
		cursor = map[(cursor->x + mapWidth * cursor->y) + mapWidth];
		cursor->bCursor = true;
	}
	else if (input == EKey::LEFT && cursor->x > 0)
	{
		cursor->bCursor = false;
		cursor = map[(cursor->x + mapWidth * cursor->y) - 1];
		cursor->bCursor = true;
	}
	else if (input == EKey::RIGHT && cursor->x < mapWidth - 1)
	{
		cursor->bCursor = false;
		cursor = map[(cursor->x + mapWidth * cursor->y) + 1];
		cursor->bCursor = true;
	}
	else if (input == EKey::SPACE)
	{
		cursor->mapState = EMapState::EMPTY;
	}
	else if (input == '1')
	{
		cursor->mapState = EMapState::WALL;
	}
	else if (input == '2')
	{
		cursor->mapState = EMapState::LOOF;
	}
	else if (input == '3')
	{
		cursor->mapState = EMapState::BRICK;
	}
	else if (input == '4')
	{
		cursor->mapState = EMapState::PO_VIL_BA;
	}
	else if (input == '5')
	{
		cursor->mapState = EMapState::PO_BA_VIL;
	}
	else if (input == '6')
	{
		cursor->mapState = EMapState::PO_BA_BO;
	}
	else if (input == '7')
	{
		cursor->mapState = EMapState::PO_BO_BA;
	}

	return input;
}

void Map::EditMap(int x, int y, EMapState mapState)
{
	map[x + mapWidth * y]->mapState = mapState;
}

EMapState Map::GetMapState(int x, int y)
{
	return map[x + mapWidth * y]->mapState;
}

Position * Map::GetPosition(int x, int y)
{
	return map[x + mapWidth * y];
}
