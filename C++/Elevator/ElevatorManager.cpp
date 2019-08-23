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
	push_back(1, 500, 5);
	push_back(1, 500, 5);
	push_back(1, 500, 5);
	push_back(1, 500, 5);

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
	Elevator* closerElevator;
	Elevator* anotherCloserElevator;

	for (int i = 0; i < buttons.size(); i++)
	{
		closerElevator =  FindElevator(i);

		if (closerElevator != nullptr)
		{
			if ((closerElevator->direction == EDirection::UP || closerElevator->direction == EDirection::Stop)
				&& closerElevator->targetFloor < i)
			{
				closerElevator->targetFloor = i;
			}
			else if ((closerElevator->direction == EDirection::Down || closerElevator->direction == EDirection::Stop)
				&& closerElevator->targetFloor > i)
			{
				closerElevator->targetFloor = i;
			}

			// 위아래 동시에 버튼이 눌린 경우
			/*if (buttons[i].btn.up && buttons[i].btn.down)
			{
				anotherCloserElevator = FindElevatorAnother(i, closerElevator);
				if (anotherCloserElevator != nullptr)
				{
					if ((anotherCloserElevator->direction == EDirection::Down || anotherCloserElevator->direction == EDirection::Stop)
						&& anotherCloserElevator->targetFloor > i)
					{
						anotherCloserElevator->targetFloor = i;
					}
				}
			}*/
		}
	}
}

Elevator* ElevatorManager::FindElevator(int _floor)
{
	int closerElevatorDistance = 100;
	int elevatorDistance;
	vector<pair<Elevator*, int>> elevatorsDistanceVec;
	Elevator* closerElevatorIter = nullptr;

	// 엘리베이터 거리 계산
	if (buttons[_floor].btn.up || buttons[_floor].btn.down)
	{
		for (vector<Elevator*>::iterator iter = elevators.begin(); iter != elevators.end(); iter++)
		{
			elevatorDistance = abs((*iter)->floor - _floor);
			elevatorsDistanceVec.push_back(make_pair(*iter, elevatorDistance));
		}
	}

	// 정지 or 같은방향 엘리베이터 중 가까운 엘리베이터 탐색
	for (vector<pair<Elevator*, int>>::iterator iter = elevatorsDistanceVec.begin(); iter != elevatorsDistanceVec.end(); iter++)
	{
		if (((*iter).first->direction == EDirection::UP && (*iter).first->floor < _floor)
			|| ((*iter).first->direction == EDirection::Down && (*iter).first->floor > _floor)
			||(*iter).first->direction == EDirection::Stop)
		{
			if (closerElevatorDistance > (*iter).second)
			{
				closerElevatorDistance = (*iter).second;
				closerElevatorIter = (*iter).first;
			}
		}
	}
	
	return closerElevatorIter;
}

Elevator* ElevatorManager::FindElevatorAnother(int _floor, Elevator* _anotherCloserElevator)
{
	int closerElevatorDistance = 100;
	int elevatorDistance;
	vector<pair<Elevator*, int>> elevatorsDistanceVec;
	Elevator* closerElevatorIter = nullptr;
	Elevator* anotherCloserElevator = nullptr;

	// 엘리베이터 거리 계산
	if (buttons[_floor].btn.up || buttons[_floor].btn.down)
	{
		for (vector<Elevator*>::iterator iter = elevators.begin(); iter != elevators.end(); iter++)
		{
			elevatorDistance = abs((*iter)->floor - _floor);
			elevatorsDistanceVec.push_back(make_pair(*iter, elevatorDistance));
		}
	}

	// 정지 or 같은방향 엘리베이터 중 가까운 엘리베이터 탐색
	for (vector<pair<Elevator*, int>>::iterator iter = elevatorsDistanceVec.begin(); iter != elevatorsDistanceVec.end(); iter++)
	{
		if (((*iter).first->direction == EDirection::UP && (*iter).first->floor < _floor)
			|| ((*iter).first->direction == EDirection::Down && (*iter).first->floor > _floor)
			|| (*iter).first->direction == EDirection::Stop)
		{
			if (closerElevatorDistance > (*iter).second)
			{
				closerElevatorDistance = (*iter).second;
				closerElevatorIter = (*iter).first;
			}
		}
	}

	// 정지 or 같은방향 엘리베이터 중 다음으로 가까운 엘리베이터 탐색
	for (vector<pair<Elevator*, int>>::iterator iter = elevatorsDistanceVec.begin(); iter != elevatorsDistanceVec.end(); iter++)
	{
		if (((*iter).first->direction == EDirection::UP && (*iter).first->floor < _floor)
			|| ((*iter).first->direction == EDirection::Down && (*iter).first->floor > _floor)
			|| (*iter).first->direction == EDirection::Stop
			&& (*iter).first != closerElevatorIter)
		{
			if (closerElevatorDistance > (*iter).second)
			{
				closerElevatorDistance = (*iter).second;
				anotherCloserElevator = (*iter).first;
			}
		}
	}

	return anotherCloserElevator;
}