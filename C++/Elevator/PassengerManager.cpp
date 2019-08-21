#include "PassengerManager.h"

PassengerManager::PassengerManager()
{
	passengers.reserve(100);
}


PassengerManager::~PassengerManager()
{
}

void PassengerManager::push_back(int _passengerNum, int _weight)
{
	//passengers.push_back(make_shared<Passenger>(new Passenger(_passengerNum, _weight)));
	passengers.push_back(new Passenger(_passengerNum, _weight));
}
