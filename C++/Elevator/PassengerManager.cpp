#include "PassengerManager.h"

bool Pred(Passenger* passenger)
{
	return passenger->floor == passenger->targetFloor;
}

PassengerManager::PassengerManager()
{
	srand(time(nullptr));
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
		CheckCanBoard(*iter, (*iter)->closerElevatorIter->num - 1);
		CarryPassenger(*iter);
		CheckGetOff(iter, (*iter)->closerElevatorIter->num - 1);
	}

	// 하차한 탑승자 제거
	passengers.remove_if(Pred);
}

void PassengerManager::CheckCanBoard(Passenger* _passenger, int _elevatorNum)
{
	if (_passenger->floor == elevatorManager->elevators[_elevatorNum]->floor)
	{
		OffButtion(_passenger, _elevatorNum);

		// 방향이 같은 경우
		if (_passenger->direction == EDirection::UP && _passenger->direction == elevatorManager->elevators[_elevatorNum]->direction
			&& _passenger->targetFloor > elevatorManager->elevators[_elevatorNum]->targetFloor)
		{
			elevatorManager->elevators[_elevatorNum]->targetFloor = _passenger->targetFloor;
		}
		else if (_passenger->direction == EDirection::Down && _passenger->direction == elevatorManager->elevators[_elevatorNum]->direction
			&& _passenger->targetFloor < elevatorManager->elevators[_elevatorNum]->targetFloor)
		{
			elevatorManager->elevators[_elevatorNum]->targetFloor = _passenger->targetFloor;
		}
		// 방향이 다른 경우
		else if (_passenger->direction != elevatorManager->elevators[_elevatorNum]->direction)
		{
			elevatorManager->elevators[_elevatorNum]->nextTargetFloor = _passenger->targetFloor;
		}

		_passenger->isBoard = true;
		_passenger->elevatorNum = elevatorManager->elevators[_elevatorNum]->num;
	}
}

list<Passenger*>::iterator PassengerManager::CheckGetOff(list<Passenger*>::iterator _passenger, int _elevatorNum)
{
	if ((*_passenger)->targetFloor == (*_passenger)->floor)
	{
		(*_passenger)->isBoard = false;
		return _passenger;
	}
	else
	{
		return passengers.end();
	}
}

void PassengerManager::CarryPassenger(Passenger * _passenger)
{
	if (_passenger->isBoard)
	{
		_passenger->floor = elevatorManager->elevators[_passenger->elevatorNum - 1]->floor;
	}
}

void PassengerManager::OffButtion(Passenger* _passenger, int _elevatorNum)
{
	if (_elevatorNum == 0)
	{
		elevatorManager->buttons[_passenger->floor].btn1.up = false;
		elevatorManager->buttons[_passenger->floor].btn1.down = false;
	}
	else if (_elevatorNum == 1)
	{
		elevatorManager->buttons[_passenger->floor].btn2.up = false;
		elevatorManager->buttons[_passenger->floor].btn2.down = false;
	}
	else if (_elevatorNum == 2)
	{
		elevatorManager->buttons[_passenger->floor].btn3.up = false;
		elevatorManager->buttons[_passenger->floor].btn3.down = false;
	}
	else if (_elevatorNum == 3)
	{
		elevatorManager->buttons[_passenger->floor].btn4.up = false;
		elevatorManager->buttons[_passenger->floor].btn4.down = false;
	}
}

