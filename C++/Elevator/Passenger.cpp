#include "Passenger.h"


Passenger::Passenger()
{
	weight = 0;
	floor = 0;
	targetFloor = 0;
	elevatorNum = 0;
	elevatorManager = nullptr;
	pressBtn = false;
	isBoard = false;
	closerElevatorIter = nullptr;
}

Passenger::Passenger(int _weight, int _floor, int _targetFloor, ElevatorManager* _elevatorManager)
{
	weight = _weight;
	floor = _floor;
	targetFloor = _targetFloor;
	elevatorManager = _elevatorManager;
	pressBtn = false;
	isBoard = false;
	closerElevatorIter = nullptr;
}


Passenger::~Passenger()
{
}

void Passenger::CallElevator()
{
	if (!pressBtn)
	{
		Elevator* closerElevatorIter = FindCloserElevator();
		PressButton(closerElevatorIter);
	}
}

void Passenger::PressButton(Elevator* _closerElevator)
{
	if (_closerElevator->num == 1)
	{
		elevatorManager->buttons[floor].btn1.up = true;
		pressBtn = true;
	}
	else if (_closerElevator->num == 2)
	{
		elevatorManager->buttons[floor].btn2.up = true;
		pressBtn = true;
	}
	else if (_closerElevator->num == 3)
	{
		elevatorManager->buttons[floor].btn3.up = true;
		pressBtn = true;
	}
	else if (_closerElevator->num == 4)
	{
		elevatorManager->buttons[floor].btn4.up = true;
		pressBtn = true;
	}
}

Elevator* Passenger::FindCloserElevator()
{
	int closerElevator = 100;
	for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
	{
		if (closerElevator > abs((*iter)->floor - floor))
		{
			closerElevator = abs((*iter)->floor - floor);
			closerElevatorIter = *iter;
		}
	}

	return closerElevatorIter;
}
