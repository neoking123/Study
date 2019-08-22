#include "PassengerManager.h"

PassengerManager::PassengerManager()
{
	srand(time(nullptr));
}


PassengerManager::~PassengerManager()
{
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
	list<Passenger*>::iterator checkGetOffIter;
	//vector<list<Passenger*>::iterator> checkGetOffIter;
	for(list<Passenger*>::iterator iter = passengers.begin(); iter != passengers.end(); iter++)
	{
		(*iter)->CallElevator();
		CheckCanBoard(*iter, (*iter)->closerElevatorIter->num - 1);
		CarryPassenger(*iter);
		checkGetOffIter = CheckGetOff(iter, (*iter)->closerElevatorIter->num - 1);
		//checkGetOffIter.push_back(CheckGetOff(iter, (*iter)->closerElevatorIter->num - 1));
		GetOffPassenger(checkGetOffIter);
	}

	
}

void PassengerManager::CheckCanBoard(Passenger* _passenger, int _elevatorNum)
{
	if (_passenger->floor == elevatorManager->elevators[_elevatorNum]->floor)
	{
		OffButtion(_passenger, _elevatorNum);
		elevatorManager->elevators[_elevatorNum]->targetFloor = _passenger->targetFloor;
		_passenger->isBoard = true;
		_passenger->elevatorNum = elevatorManager->elevators[_elevatorNum]->num;
	}
}

void PassengerManager::GetOffPassenger(list<Passenger*>::iterator _passenger)
{
	if (_passenger != passengers.end())
	{
		passengers.erase(_passenger);
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

