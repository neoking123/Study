#include "ElevatorManager.h"

ElevatorManager::ElevatorManager()
{
	elevators.reserve(10);
	elevatorCount = 0;
}


ElevatorManager::~ElevatorManager()
{
}

void ElevatorManager::push_back(int _floor, int _weightMax, int _passengerMax)
{
	/*shared_ptr<Elevator> newElevator = make_shared<Elevator>(new Elevator(_num, _floor, _weightMax, _passengerMax));
	Elevators.push_back(newElevator);*/
	elevatorCount++;
	elevators.push_back(new Elevator(elevatorCount, _floor, _weightMax, _passengerMax));
}

void ElevatorManager::Init()
{
	push_back(1, 600, 10);
	push_back(1, 600, 10);
	push_back(1, 600, 10);
	push_back(1, 600, 10);
}
