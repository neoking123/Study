#pragma once
#include <iostream>
#include <vector>
#include "ElevatorManager.h"
using namespace std;

#define WIDTH 20
#define HEIGHT 20

enum EmapType
{
	WALL,
	PASSENGER,
	ELEVATOR
};

class PrintManager
{
public:
	//int building[HEIGHT][WIDTH];
	vector<int> building;
	ElevatorManager elevatorManager;

public:
	PrintManager();
	~PrintManager();

	void Print();
};

