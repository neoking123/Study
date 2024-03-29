#include "pch.h"
#include <iostream>
#include <conio.h>

using namespace std;

#define WIDTH 19
#define HEIGHT 19

int map[HEIGHT][WIDTH] = 
{ 
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0 },
	{ 0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0 },
	{ 0,1,3,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};

void Init()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			map[y][x] = 0;
		}

		cout << endl;
	}
}

void OperateInput(int* cursorX, int* cursorY, bool* exit)
{
	char input = _getch(); // <conio.h>

	system("cls");
	
	if (input == 'w')
	{
		if (*cursorY > 1 && map[*cursorY - 1][*cursorX] != 0)
		{
			// 아이템
			if (map[*cursorY - 1][*cursorX] == 2)
			{
				map[*cursorY - 1][*cursorX] = 1;
				(*cursorY)--;
			}
			// 상자
			else if (map[*cursorY - 1][*cursorX] == 3)
			{
				if (*cursorY - 2 > 0 && map[*cursorY - 2][*cursorX] != 0)
				{
					map[*cursorY - 1][*cursorX] = 1;
					map[*cursorY - 2][*cursorX] = 3;
					(*cursorY)--;
				}
			}
			else
				(*cursorY)--;
		}
	}
	else if (input == 's')
	{
		if (*cursorY < HEIGHT - 2 && map[*cursorY + 1][*cursorX] != 0)
		{
			if (map[*cursorY + 1][*cursorX] == 2)
			{
				map[*cursorY + 1][*cursorX] = 1;
				(*cursorY)++;
			}
			else if (map[*cursorY + 1][*cursorX] == 3)
			{
				if (*cursorY + 3 < HEIGHT && map[*cursorY + 2][*cursorX] != 0)
				{
					map[*cursorY + 1][*cursorX] = 1;
					map[*cursorY + 2][*cursorX] = 3;
					(*cursorY)++;
				}
			}
			else
				(*cursorY)++;
		}
	}
	else if (input == 'a' && map[*cursorY][*cursorX - 1] != 0)
	{
		if (*cursorX > 1)
		{
			if (map[*cursorY][*cursorX - 1] == 2)
			{
				map[*cursorY][*cursorX - 1] = 1;
			}
			else if (map[*cursorY][*cursorX - 1] == 3)
			{
				if (*cursorX - 2 > 0 && map[*cursorY][*cursorX - 2] != 0)
				{
					map[*cursorY][*cursorX - 1] = 1;
					map[*cursorY][*cursorX - 2] = 3;
					(*cursorX)--;
				}
			}
			else
				(*cursorX)--;
		}
	}
	else if (input == 'd' && map[*cursorY][*cursorX + 1] != 0)
	{
		if (*cursorX < WIDTH - 2)
		{
			if (map[*cursorY][*cursorX + 1] == 2)
			{
				map[*cursorY][*cursorX + 1] = 1;
			}
			else if (map[*cursorY][*cursorX + 1] == 3)
			{
				if (*cursorX + 3 < WIDTH && map[*cursorY][*cursorX + 2] != 0)
				{
					map[*cursorY][*cursorX + 1] = 1;
					map[*cursorY][*cursorX + 2] = 3;
					(*cursorX)++;
				}
			}
			else
				(*cursorX)++;
		}
	}
	else if (input == 'q')
	{
		*exit = true;
	}
}

void DrawMap(int cursorX, int cursorY)
{
	// 0 : 벽
	// 1 : 이동가능
	// 2 : 이동가능 벽
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x == cursorX && y == cursorY)
			{
				cout << "☆";
			}
			else if (map[y][x] == 0)
			{
				cout << "▨";
			}
			else if (map[y][x] == 1)
			{
				cout << "  ";
			}
			else if (map[y][x] == 2)
			{
				cout << "♣";
			}
			else if (map[y][x] == 3)
			{
				cout << "●";
			}
		}

		cout << endl;
	}
}

int main()
{
	int cursorX = WIDTH / 2;
	int cursorY = HEIGHT / 2;
	bool exit = false;

	while (!exit)
	{
		OperateInput(&cursorX, &cursorY, &exit);
		DrawMap(cursorX, cursorY);
	}

	return 0;
}