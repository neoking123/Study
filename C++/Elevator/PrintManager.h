#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "ElevatorManager.h"
#include "PassengerManager.h"
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
	vector<int> building;
	ElevatorManager* elevatorManager;
	PassengerManager* passengerManager;

public:
	PrintManager();
	~PrintManager();

	void Print();
};

