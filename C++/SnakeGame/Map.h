#pragma once
#include <iostream>
#include <time.h>
using namespace std;

#define WIDTH 40
#define HEIGHT 20

enum mapState
{
	WALL,
	EMPTY,
	PLAYER,
	BODY,
	ENEMY
};

class Map
{
public:
	int arrMap[HEIGHT][WIDTH];

	Map();
	~Map();

	void Init();
	void Draw();
	void SetMap();
	void SpawnEnemy();
};

