#include <iostream>
using namespace std;

template <typename T, typename T2>
T Sum(T a, T2 b)
{
	return a + b;
}


int main()
{
	Sum(1, 2);


	return 0;
}