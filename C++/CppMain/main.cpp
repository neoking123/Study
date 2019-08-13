#include <iostream>
#include <assert.h>
#include "Map.h"
#include "Player.h"
using namespace std;

class POINT
{
public:
	int x;
	int y;

	POINT operator+(POINT& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}
};

int main()
{
	POINT a, b;
	POINT c = a + b;

	//__FILE__
	//__LINE__

	//assert(a == 10);


	return 0;
}