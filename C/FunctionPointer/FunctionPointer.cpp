#include "pch.h"
#include <iostream>
using namespace std;

int sum(int a, int b)
{
	return a + b;
}

typedef int(*FN_TYPE)(int, int);

int main()
{
	//void(*pfun)();
	//pfun = &print;
	//(*pfun)();

	FN_TYPE pfun;
	pfun = sum;
	cout << pfun(5, 7);

	return 0;
}
