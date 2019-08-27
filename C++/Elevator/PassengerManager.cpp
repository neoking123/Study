#include "PassengerManager.h"

bool Pred(Passenger* passenger)
{
	return passenger->floor == passenger->targetFloor;
}

PassengerManager::PassengerManager()
{
	srand(time(nullptr));
	passengerNum = 0;
	exitPassengerCount = 0;
	sumBoardTime = 0;
}

PassengerManager::~PassengerManager()
{
	list<Passenger*>::iterator titer;
	for (list<Passenger*>::iterator iter = passengers.begin(); iter != passengers.end(); iter++)
	{
		titer = iter;
		delete *iter;
		iter = titer;
	}
}

void PassengerManager::RandomSpawn()
{
	int randomWeight = rand() % 60 + 40;
	int randomFloor = rand() % 20 + 1;
	int randomTargetFloor = rand() % 20 + 1;

	while (randomFloor == randomTargetFloor)
	{
		randomTargetFloor = rand() % 20 + 1;
	}
	passengers.push_back(new Passenger(randomWeight, randomFloor, randomTargetFloor, elevatorManager));
}

void PassengerManager::UpdatePassengers()
{
	for(list<Passenger*>::iterator iter = passengers.begin(); iter != passengers.end(); iter++)
	{
		(*iter)->CallElevator();
		(*iter)->Waitting();
		CheckCanBoard(*iter);
		CarryPassenger(*iter);
		CheckGetOff(iter, (*iter)->elevatorNum);
	}

	// 하차한 탑승자 제거
	passengers.remove_if(Pred);
}

void PassengerManager::CheckCanBoard(Passenger* _passenger)
{
	for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
	{
		if (_passenger->floor == (*iter)->floor && !_passenger->isBoard 
			&& (*iter)->weightMax >= (*iter)->CurrentWeight + _passenger->weight
			&& (*iter)->passengerMax >= (*iter)->CurrentPasssengerCount)
		{
			// 방향이 같은 경우
			if (_passenger->direction == EDirection::UP
				&& (_passenger->direction == (*iter)->direction || (*iter)->direction == EDirection::Stop))
			{
				if (_passenger->targetFloor > (*iter)->targetFloor)
				{
					(*iter)->targetFloor = _passenger->targetFloor;
				}

				BoardElevator(_passenger, iter);
			}
			else if (_passenger->direction == EDirection::Down
				&& (_passenger->direction == (*iter)->direction || (*iter)->direction == EDirection::Stop))
			{
				if (_passenger->targetFloor < (*iter)->targetFloor)
				{
					(*iter)->targetFloor = _passenger->targetFloor;
				}

				BoardElevator(_passenger, iter);
			}
			// 방향이 다른 경우
			else if (_passenger->direction == EDirection::UP
				&&_passenger->direction != (*iter)->direction 
				&& _passenger->floor == (*iter)->targetFloor
				&& _passenger->targetFloor > (*iter)->targetFloor)
			{
				if (_passenger->targetFloor > (*iter)->targetFloor)
				{
					(*iter)->targetFloor = _passenger->targetFloor;
				}

				BoardElevator(_passenger, iter);
			}
			else if (_passenger->direction == EDirection::Down
				&&_passenger->direction != (*iter)->direction
				&& _passenger->floor == (*iter)->targetFloor
				&& _passenger->targetFloor < (*iter)->targetFloor)
			{
				if (_passenger->targetFloor < (*iter)->targetFloor)
				{
					(*iter)->targetFloor = _passenger->targetFloor;
				}

				BoardElevator(_passenger, iter);
			}
		}
	}
}

void PassengerManager::BoardElevator(Passenger * _passenger, vector<Elevator*>::iterator iter)
{
	OffButtion(_passenger);
	_passenger->isBoard = true;
	_passenger->elevatorNum = (*iter)->num;
	(*iter)->CurrentPasssengerCount++;
	(*iter)->CurrentWeight += _passenger->weight;
}

list<Passenger*>::iterator PassengerManager::CheckGetOff(list<Passenger*>::iterator _passenger, int _elevatorNum)
{
	if ((*_passenger) != nullptr)
	{
		if ((*_passenger)->targetFloor == (*_passenger)->floor)
		{
			(*_passenger)->isBoard = false;
			elevatorManager->elevators[_elevatorNum - 1]->CurrentPasssengerCount--;
			elevatorManager->elevators[_elevatorNum - 1]->CurrentWeight -= (*_passenger)->weight;
			sumBoardTime += (*_passenger)->waitTime;
			exitPassengerCount++;
			return _passenger;
		}
		else
		{
			return passengers.end();
		}
	}
}

void PassengerManager::CarryPassenger(Passenger * _passenger)
{
	if (_passenger->isBoard)
	{
		_passenger->floor = elevatorManager->elevators[_passenger->elevatorNum - 1]->floor;
	}
}

void PassengerManager::OffButtion(Passenger* _passenger)
{
	if (_passenger->direction == EDirection::UP)
	{
		elevatorManager->buttons[_passenger->floor].btn.up = false;
	}
	else if (_passenger->direction == EDirection::Down)
	{
		elevatorManager->buttons[_passenger->floor].btn.down = false;
	}
}

float PassengerManager::GetAvgWaitTime()
{
	return (float)sumBoardTime / exitPassengerCount;
}