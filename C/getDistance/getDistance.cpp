#include "pch.h"
#include <iostream>
#include <cmath>
using namespace std;

float getDistance(int x1, int y1, int x2, int y2)
{
	return sqrtf(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main()
{
	cout << getDistance(0, 0, 3, 5);
	//cout << pow(2, 2) << endl;
	//cout << sqrtf(4) << endl;
}