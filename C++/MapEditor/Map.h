#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <Windows.h>
using namespace std;

enum EKey
{
	UP = 0x48,
	LEFT = 0x4B,
	RIGHT = 0x4D,
	DOWN = 0x50,
	SPACE = 0x20,
	CONFIRM = 'x',
	CANCLE = 'z'
};

enum EMapState
{
	EMPTY,
	WALL,
	PLAYER,
	LOOF,
	BRICK,
	MONSTER,
	BOSS,
	PO_VIL_BA,
	PO_BA_VIL,
	PO_BA_BO,
	PO_BO_BA
};

class Position
{
public:
	int x;
	int y;
	bool bCursor;
	bool bPlayer;
	bool bMonster;
	bool bBoss;
	EMapState mapState;
	
public:

	Position()
	{
		x = 0;
		y = 0;
		mapState = EMPTY;
		bCursor = false;
		bPlayer = false;
		bMonster = false;
		bBoss = false;
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
	int GetMapWidth();
	int GetMapHeight();
	void Draw();
	void PrintMenu();
	void CreateCursor();
	void DeleteCursor();
	char InputCursor();
	void EditMap(int x, int y, EMapState mapState);
	EMapState GetMapState(int x, int y);
	Position* GetPosition(int x, int y);
};

