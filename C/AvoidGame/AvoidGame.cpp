#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

#define FPS 30.0f
#define WIDTH 12
#define HEIGHT 20

int map[HEIGHT][WIDTH] = {};
int playerX = 0;
int playerY = 0;
int enemyCount = 0;
int score = 0;
bool quit = false;
float fps = 30.0f;
int spawnCount = 3;

struct Enemy
{
	int posX;
	int posY;
	
	int curTime;
	int spawnTime;
	int speed;

	Enemy(int newPosX = 0, int newPosY = 0, int newCurTime = 0, int newSpawnTime = 0, int newSpeed = 0)
	{
		posX = newPosX;
		posY = newPosY;
		curTime = newCurTime;
		spawnTime = newSpawnTime;
		speed = newSpeed;
	}
};

Enemy enemys[1024];

enum eMap
{
	EMPTY,
	WALL,
	PLAYER,
	ENERMY,
};

// enemy 랜덤위치 스폰
void RandomSpawnEnermy(Enemy& enemy)
{
	enemy.posX = (rand() % (WIDTH - 2)) + 1;
	enemy.posY = 0;

	map[enemy.posY][enemy.posX] = ENERMY;
	enemyCount++;
}

// enemy 아래로 이동
void MoveDownEnemy()
{
	for (int i = 0; i < enemyCount; i++)
	{
		if (enemys[i].posY < HEIGHT - 1)
		{
			if (map[enemys[i].posY + 1][enemys[i].posX] == PLAYER)
			{
				quit = true;
				break;
			}
			else if (map[enemys[i].posY + 1][enemys[i].posX] == EMPTY || map[enemys[i].posY + 1][enemys[i].posX] == ENERMY)
			{
				if (enemys[i].curTime > enemys[i].spawnTime)
				{
					map[enemys[i].posY + 1][enemys[i].posX] = ENERMY;
					map[enemys[i].posY][enemys[i].posX] = EMPTY;
					enemys[i].posY++;
					enemys[i].curTime = 0;
				}
				else
				{
					enemys[i].curTime += enemys[i].speed;
				}
			}
		}
		else if (enemys[i].posY == HEIGHT - 1)
		{
			score += 100;
			map[enemys[i].posY][enemys[i].posX] = EMPTY;
			enemys[i].posY++;
		}
	}
}

// 입력
void Input()
{
	if (_kbhit())
	{
		char ch = _getch();

		if (ch == 'a' && map[playerY][playerX - 1] != WALL)
		{
			map[playerY][playerX - 1] = PLAYER;
			map[playerY][playerX] = EMPTY;
			playerX--;
		}
		else if(ch == 'd' && map[playerY][playerX + 1] != WALL)
		{
			map[playerY][playerX + 1] = PLAYER;
			map[playerY][playerX] = EMPTY;
			playerX++;
		}
		else if (ch == '+')
		{
			fps += 5;
		}
		else if (ch == '-')
		{
			fps -= 5;
		}
	}
}

// 초기화
void Init()
{
	srand(time(nullptr));

	playerX = WIDTH / 2;
	playerY = HEIGHT - 1;

	// 맵 설정
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x == playerX && y == playerY)
			{
				map[y][x] = PLAYER;
			}
			else if (x == 0 || x == WIDTH - 1)
			{
				map[y][x] = WALL;
			}
			else
			{
				map[y][x] = EMPTY;
			}	
		}
	}
}

// 업데이트
void Update()
{
	// enemy 스폰
	if (spawnCount == 0)
	{
		Enemy enemy(0, 0, 0, 1, ((rand() % 4) + 1));
		enemys[enemyCount] = enemy;

		RandomSpawnEnermy(enemys[enemyCount]);
		spawnCount = 3;
	}
	spawnCount--;

	MoveDownEnemy();
}

// 출력
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

	cout << endl;
	cout << endl;
	cout << "\tScore : " << score << endl;
	//cout << "\tSpeed : " << fps << endl;
}

void Release()
{

}

int main()
{
	Init();

	while (!quit)
	{
		Input();
		Update();
		Draw();
		//Sleep(1000 / fps);
	}

	cout << "\t※Game Over※" << endl;

	Release();

	return 0;
}