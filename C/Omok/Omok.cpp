#include "pch.h"
#include <iostream>
#include <conio.h>

#define WIDTH 19
#define HEIGHT 19
#define EMPTY 0
#define BLACK 1
#define WHITE 2

using namespace std;

int main()
{
	int cursorX = WIDTH / 2;
	int cursorY = HEIGHT / 2;
	char map[HEIGHT][WIDTH] = {};
	int turn = 0;
	int countX = 1;
	int countY = 1;
	int i = 1;
	int j = 1;
	bool bCursor = false;

	while (true)
	{
		/*char input;
		cin >> input;*/

		char input = _getch(); // <conio.h>

		system("cls");

		// Input
		if (input == 'w')
		{
			if (cursorY > 0)
			{
				cursorY--;
			}
			bCursor = false;
		}
		else if (input == 's')
		{
			if (cursorY < HEIGHT - 1)
			{
				cursorY++;
			}
			bCursor = false;
		}
		else if (input == 'a')
		{
			if (cursorX > 0)
			{
				cursorX--;
			}
			bCursor = false;
		}
		else if (input == 'd')
		{
			if (cursorX < WIDTH - 1)
			{
				cursorX++;
			}
			bCursor = false;
		}
		else if (input == 'z')
		{
			if (turn % 2 == 0 && map[cursorY][cursorX] == EMPTY)
			{
				map[cursorY][cursorX] = BLACK;
				turn++;
				bCursor = true;
			}
			else if (map[cursorY][cursorX] == EMPTY)
			{
				map[cursorY][cursorX] = WHITE;
				turn++;
				bCursor = true;
			}

			// 흑돌 체크
			if (turn % 2 == 1)
			{
				i = 1;
				j = 1;
				countX = 1;
				countY = 1;

				// X 앞검사
				while (countX != 5)
				{
					if (map[cursorY][cursorX + i] == BLACK)
					{
						countX++;
						i++;
					}
					else
						break;
				}

				i = 1;
				// X 뒤검사
				while (countX != 5)
				{
					if (map[cursorY][cursorX - i] == BLACK)
					{
						countX++;
						i++;
					}
					else
						break;
				}

				// 왼위

				// Y 앞검사
				while (countY != 5)
				{
					if (map[cursorY + j][cursorX] == BLACK)
					{
						countY++;
						j++;
					}
					else
						break;
				}

				j = 1;
				// Y 뒤검사
				while (countY != 5)
				{
					if (map[cursorY - j][cursorX] == BLACK)
					{
						countY++;
						j++;
					}
					else
						break;
				}
			}
			// 백돌 체크
			else if (turn % 2 == 0)
			{
				i = 1;
				j = 1;
				countX = 1;
				countY = 1;

				// X 앞검사
				while (countX != 5)
				{
					if (map[cursorY][cursorX + i] == WHITE)
					{
						countX++;
						i++;
					}
					else
						break;
				}

				i = 1;
				// X 뒤검사
				while (countX != 5)
				{
					if (map[cursorY][cursorX - i] == WHITE)
					{
						countX++;
						i++;
					}
					else
						break;
				}

				// Y 앞검사
				while (countY != 5)
				{
					if (map[cursorY + j][cursorX] == WHITE)
					{
						countY++;
						j++;
					}
					else
						break;
				}

				j = 1;
				// Y 뒤검사
				while (countY != 5)
				{
					if (map[cursorY - j][cursorX] == WHITE)
					{
						countY++;
						j++;
					}
					else
						break;
				}
			}
		}

		// Draw
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				if (x == cursorX && y == cursorY && !bCursor)
				{
					cout << "☆";
				}
				else if (map[y][x] == BLACK)
				{
					cout << "○";
				}
				else if (map[y][x] == WHITE)
				{
					cout << "●";
				}
				else if (x == 0 && y == 0)
				{
					cout << "┌";
				}
				else if (x == 0 && y == HEIGHT - 1)
				{
					cout << "└";
				}
				else if (x == WIDTH - 1 && y == 0)
				{
					cout << "┐";
				}
				else if (x == WIDTH - 1 && y == HEIGHT - 1)
				{
					cout << "┘";
				}
				else if (x == 0)
				{
					cout << "├";
				}
				else if (x == WIDTH - 1)
				{
					cout << "┤";
				}
				else if (y == 0)
				{
					cout << "┬";
				}
				else if (y == HEIGHT - 1)
				{
					cout << "┴";
				}
				else
				{
					cout << "┼";
				}
			}

			cout << endl;
		}

		cout << "턴수 : " << turn + 1 << endl;
		if (turn % 2 == 0)
		{
			cout << "턴 : 흑";
		}
		else
			cout << "턴 : 백";

		if (turn % 2 == 1 && (countX == 5 || countY == 5))
		{
			cout << endl;
			cout << "흑 승리" << endl;
			break;
		}
		else if (turn % 2 == 0 && (countX == 5 || countY == 5))
		{
			cout << endl;
			cout << "백 승리" << endl;
			break;
		}
	}

	cout << "끝" << endl;
	while (true)
	{

	}

	return 0;
}