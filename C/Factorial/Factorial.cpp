#include "pch.h"
#include <iostream>
using namespace std;

// n! == n * (n -1)!
// 1! == 1
int Factorial(int n)
{
	if (n == 1)
		return 1;
	else
	{
		return n * Factorial(n - 1);
	}

}

int main()
{
	cout << Factorial(10);
}