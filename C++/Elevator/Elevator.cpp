#include "Elevator.h"

Elevator::Elevator()
{
	num = 0;
	floor = 0;
	weightMax = 0;
	passengerMax = 0;
	targetFloor = 0;
	CurrentPasssengerCount = 0;
	CurrentWeight = 0;
	isMove = false;
	direction = EDirection::Stop;
}

Elevator::Elevator(int _num, int _floor, int _weightMax, int _passengerMax, int _targetFloor)
{
	num = _num;
	floor = _floor;
	weightMax = _weightMax;
	passengerMax = _passengerMax;
	targetFloor = _targetFloor;
	CurrentPasssengerCount = 0;
	CurrentWeight = 0;
	isMove = false;
	direction = EDirection::Stop;
}

Elevator::~Elevator()
{
}

void Elevator::MoveTargetFloor()
{
	if (floor < targetFloor)
	{
		floor++;
		isMove = true;
		direction = EDirection::UP;
	}
	else if (floor > targetFloor)
	{
		floor--;
		isMove = true;
		direction = EDirection::Down;
	}
	else
	{
		isMove = false;
		direction = EDirection::Stop;
	}
}
