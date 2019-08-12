#pragma once
#include <iostream>
using namespace std;

#define WIDTH 19
#define HEIGHT 19

enum mapState
{
	EMPTY,
	WALL,
	PLAYER
};

class Map
{
public:
	int aMap[HEIGHT][WIDTH];

	Map();
	~Map();

	void Init();
	void Draw();
};

