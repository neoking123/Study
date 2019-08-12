#pragma once
#include <iostream>
using namespace std;

#define WIDTH 20
#define HEIGHT 20

enum mapState
{
	EMPTY,
	WALL,
	PLAYER,
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
};

