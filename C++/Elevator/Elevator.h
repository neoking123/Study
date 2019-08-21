#pragma once
class Elevator
{
public:
	Elevator();
	Elevator(int _num = 0, int _floor = 0, int _weightMax = 0, int _passengerMax = 0);
	~Elevator();

	int num;
	int floor;
	int weightMax;
	int passengerMax;
	int targetFloor;

	void MoveTargetFloor();
};

