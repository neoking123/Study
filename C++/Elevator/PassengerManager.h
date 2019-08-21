#pragma once
#include "Passenger.h"
#include <vector>
#include <memory>
using namespace std;

class PassengerManager
{
private:
	//vector<shared_ptr<Passenger>> passengers;
	vector<Passenger*> passengers;
	int passengerNum;

public:
	PassengerManager();
	~PassengerManager();

	void push_back(int _passengerNum, int _weight);
};

