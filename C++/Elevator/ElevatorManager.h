#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Elevator.h"
using namespace std;

class ButtonType
{
public:
	ButtonType()
	{
		up = false;
		down = false;
	}

	bool up;
	bool down;
};

class Button
{
public:
	ButtonType btn1;
	ButtonType btn2;
	ButtonType btn3;
	ButtonType btn4;
};

class ElevatorManager
{
public:
	vector<Elevator*> elevators;
	vector<Button> buttons;
	int elevatorCount;

public:
	ElevatorManager();
	~ElevatorManager();

	void push_back(int _floor = 0, int _weightMax = 0, int _passengerMax = 0);
	void Init();
	void UpdateElevators();
	void CheckButtons();
};

