#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

#define FPS 30.0f
#define WIDTH 10
#define HEIGHT 20

int map[HEIGHT][WIDTH] = {};
int playerX = 0;
int playerY = 0;
int tmpY[256] = {};
int rNum = 0;
int rTmp = 0;

enum eMap
{
	EMPTY,
	WALL,
	ENERMY,
};

void SpawnEnermy(int x, int y)
{
	map[y][x] = EMPTY;
	map[y + 1][x] = ENERMY;
}

void ScoreCheck()
{

}

void Input()
{
	if (_kbhit())
	{
		char ch = _getch();
		
		system("cls");

		if (ch == 'a' && playerX > 1)
		{
			playerX--;
		}
		else if(ch == 'd' && playerX < WIDTH - 2)
		{
			playerX++;
		}
	}
	/*char ch = _getch();

	system("cls");

	if (ch == 'a' && playerX > 1)
	{
		playerX--;
	}
	else if (ch == 'd' && playerX < WIDTH - 2)
	{
		playerX++;
	}*/
}

void Init()
{
	playerX = WIDTH / 2;
	playerY = HEIGHT -1;

	srand(time(nullptr));
	rNum = rand() % (WIDTH - 2) + 1;
	rTmp = rand() % (WIDTH - 2) + 1;

	for (int i = 0; i < 256; i++)
	{
		tmpY[i] = rand() % -10;
	}

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x == 0 || x == WIDTH - 1)
			{
				map[y][x] = WALL;
			}
			else
				map[y][x] = EMPTY;
		}
	}
}

void Update()
{
	SpawnEnermy(rNum, tmpY[0]++);
	SpawnEnermy(rTmp, tmpY[1]++);
	SpawnEnermy(rTmp, tmpY[2]++);

	ScoreCheck();
}

void Draw()
{
	system("cls");
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x == playerX && y == playerY)
			{
				cout << "☆";
			}
			else if (map[y][x] == EMPTY)
			{
				cout << "  ";
			}
			else if (map[y][x] == WALL)
			{
				cout << "▨";
			}
			else if (map[y][x] == ENERMY)
			{
				cout << "♥";
			}
		}
		cout << endl;
	}
}

void Release()
{

}

int main()
{
	Init();

	while (true)
	{
		Input();
		Update();
		Draw();
		Sleep(1000 / FPS);
	}

	Release();

	return 0;
}