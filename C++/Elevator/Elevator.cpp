#include "Elevator.h"

Elevator::Elevator()
{
	num = 0;
	floor = 0;
	weightMax = 0;
	passengerMax = 0;
}

Elevator::Elevator(int _num, int _floor, int _weightMax, int _passengerMax)
{
	num = _num;
	floor = _floor;
	weightMax = _weightMax;
	passengerMax = _passengerMax;
}


Elevator::~Elevator()
{
}

void Elevator::MoveTargetFloor()
{

}
