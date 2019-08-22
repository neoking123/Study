#include "Passenger.h"

Passenger::Passenger()
{
	weight = 0;
	floor = 0;
	targetFloor = 0;
	elevatorNum = 0;
	waitTime = 0;
	elevatorManager = nullptr;
	pressBtn = false;
	isBoard = false;
	closerElevatorIter = nullptr;
	direction = EDirection::Stop;
}

Passenger::Passenger(int _weight, int _floor, int _targetFloor, ElevatorManager* _elevatorManager)
{
	weight = _weight;
	floor = _floor;
	targetFloor = _targetFloor;
	elevatorManager = _elevatorManager;
	waitTime = 0;
	pressBtn = false;
	isBoard = false;
	closerElevatorIter = nullptr;

	if (_floor - _targetFloor < 0)
	{
		direction = EDirection::UP;
	}
	else if (_floor - _targetFloor > 0)
	{
		direction = EDirection::Down;
	}
}

Passenger::~Passenger()
{
}

void Passenger::CallElevator()
{
	if (!pressBtn)
	{
		closerElevatorIter = FindCloserElevator();
		PressButton(closerElevatorIter);
	}
}

void Passenger::PressButton(Elevator* _closerElevator)
{
	if (_closerElevator->num == 1)
	{
		if (direction == EDirection::UP)
		{
			elevatorManager->buttons[floor].btn1.up = true;
		}
		else if (direction == EDirection::Down)
		{
			elevatorManager->buttons[floor].btn1.down = true;
		}
		pressBtn = true;
	}
	else if (_closerElevator->num == 2)
	{
		if (direction == EDirection::UP)
		{
			elevatorManager->buttons[floor].btn2.up = true;
		}
		else if (direction == EDirection::Down)
		{
			elevatorManager->buttons[floor].btn2.down = true;
		}
		pressBtn = true;
	}
	else if (_closerElevator->num == 3)
	{
		if (direction == EDirection::UP)
		{
			elevatorManager->buttons[floor].btn3.up = true;
		}
		else if (direction == EDirection::Down)
		{
			elevatorManager->buttons[floor].btn3.down = true;
		}
		pressBtn = true;
	}
	else if (_closerElevator->num == 4)
	{
		if (direction == EDirection::UP)
		{
			elevatorManager->buttons[floor].btn4.up = true;
		}
		else if (direction == EDirection::Down)
		{
			elevatorManager->buttons[floor].btn4.down = true;
		}
		pressBtn = true;
	}
}

void Passenger::Waitting()
{
	if (!isBoard)
	{
		waitTime++;
	}
}

Elevator* Passenger::FindCloserElevator()
{
	int closerElevatorDistance = 100;
	int elevatorDistance;
	vector<pair<Elevator*, int>> elevatorsDistanceVec;
	elevatorsDistanceVec.reserve(10);

	// 엘리베이터 거리 계산
	for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
	{
		elevatorDistance = abs((*iter)->floor - floor);
		elevatorsDistanceVec.push_back(make_pair(*iter, elevatorDistance));
	}

	// 정지 or 같은 방향 엘리베이터 탐색
	for (vector<pair<Elevator*, int>>::iterator iter = elevatorsDistanceVec.begin(); iter != elevatorsDistanceVec.end(); iter++)
	{
		if ((*iter).first->direction == EDirection::Stop || (*iter).first->direction == direction)
		{
			if (closerElevatorDistance > (*iter).second)
			{
				closerElevatorDistance = (*iter).second;
				closerElevatorIter = (*iter).first;
			}
		}
	}

	if (closerElevatorIter != nullptr)
	{
		return closerElevatorIter;
	}
	else
	{
		for (vector<pair<Elevator*, int>>::iterator iter = elevatorsDistanceVec.begin(); iter != elevatorsDistanceVec.end(); iter++)
		{
			if ((*iter).first->direction != EDirection::Stop || (*iter).first->direction != direction)
			{
				if (closerElevatorDistance > (*iter).second)
				{
					closerElevatorDistance = (*iter).second;
					closerElevatorIter = (*iter).first;
				}
			}
		}
	}

	/*for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
	{
		elevatorDistance = abs((*iter)->floor - floor);

		if (closerElevatorDistance > elevatorDistance)
		{
			closerElevatorDistance = elevatorDistance;
			closerElevatorIter = *iter;
		}
	}*/
	return closerElevatorIter;
}
