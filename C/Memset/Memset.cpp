#include "pch.h"
#include <iostream>
using namespace std;

struct AAA
{
	int a;
	int b;
};

int main()
{
	AAA a;
	a.a = 10;
	a.b = 20;

	memset(&a, 0, sizeof(a));
}