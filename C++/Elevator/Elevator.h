#pragma once
#include <iostream>
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


enum EDirection
{
	Stop,
	UP,
	Down,
};

class Elevator
{
public:
	Elevator();
	Elevator(int _num = 0, int _floor = 0, int _weightMax = 0, int _passengerMax = 0, int _targetFloor = 1);
	~Elevator();

	EDirection direction;
	int num;
	int floor;
	int weightMax;
	int passengerMax;
	int targetFloor;
	bool isMove;
	int CurrentPasssengerCount;
	int CurrentWeight;

	// Ÿ�������� �̵�
	void MoveTargetFloor();
};

