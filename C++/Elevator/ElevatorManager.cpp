#include "ElevatorManager.h"

ElevatorManager::ElevatorManager()
{
	elevators.reserve(10);
	elevatorCount = 0;
	buttons.reserve(21);
}

ElevatorManager::~ElevatorManager()
{
	vector<Elevator*>::iterator titer;
	for (vector<Elevator*>::iterator iter = elevators.begin(); iter != elevators.end(); iter++)
	{
		titer = iter;
		delete *iter;
		iter = titer;
	}
}

void ElevatorManager::push_back(int _floor, int _weightMax, int _passengerMax)
{
	elevatorCount++;
	elevators.push_back(new Elevator(elevatorCount, _floor, _weightMax, _passengerMax));
}

void ElevatorManager::Init()
{
	push_back(1, 600, 10);
	push_back(15, 600, 10);
	push_back(7, 600, 10);
	push_back(8, 600, 10);

	buttons.assign(21, Button());
}

void ElevatorManager::UpdateElevators()
{
	for (vector<Elevator*>::iterator iter = elevators.begin(); iter != elevators.end(); iter++)
	{
		(*iter)->MoveTargetFloor();
	}
}

void ElevatorManager::CheckButtons()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].btn1.up || buttons[i].btn1.down)
		{
			elevators[0]->targetFloor = i;
		}

		if (buttons[i].btn2.up || buttons[i].btn2.down)
		{
			elevators[1]->targetFloor = i;
		}

		if (buttons[i].btn3.up || buttons[i].btn3.down)
		{
			elevators[2]->targetFloor = i;
		}

		if (buttons[i].btn4.up || buttons[i].btn4.down)
		{
			elevators[3]->targetFloor = i;
		}
	}
}
