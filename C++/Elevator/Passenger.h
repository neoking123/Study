#pragma once
#include <cstdlib>
#include "ElevatorManager.h"

class Passenger
{
public:
	int weight;
	int floor;
	int targetFloor;
	int elevatorNum;
	bool pressBtn;
	bool isBoard;
	ElevatorManager* elevatorManager;
	Elevator* closerElevatorIter;

public:
	Passenger();
	Passenger(int _weight = 0, int _floor = 0, int _targetFloor = 0, ElevatorManager* _elevatorManager = nullptr);
	~Passenger();

	void CallElevator();
	void PressButton(Elevator* _closerElevator);
	Elevator* FindCloserElevator();
};

