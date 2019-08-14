#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;

enum EMapState
{
	EMPTY,
	WALL,
	DOOR,
	LOOF,
	BRICK,
	PLAYER,
	MONSTER,
	BOSS,
};

class Position
{
public:
	int x;
	int y;
	bool bCursor;
	EMapState mapState;
	
public:

	Position()
	{
		x = 0;
		y = 0;
		mapState = EMPTY;
		bCursor = false;
	}

	Position(int x, int y) : Position()
	{
		this->x = x;
		this->y = y;
	}
};

class Map
{
private:
	int mapWidth;
	int mapHeight;
	vector<Position*> map;
	Position* cursor;

public:
	Map();
	~Map();

	void Init(int width, int height);
	void Draw();
	void PrintMenu();
	void CreateCursor();
	char InputCursor();
	void EditMap(int x, int y, EMapState mapState);
	EMapState GetMapState(int x, int y);
};

