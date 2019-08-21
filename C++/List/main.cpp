#include <iostream>
#include <list>
using namespace std;

bool Predicate(int first, int second)
{
	return second - first <= 0;
}

int main()
{
	list<int> lt;

	lt.push_back(10);
	lt.push_back(20);
	lt.push_back(30);
	lt.push_back(40);
	lt.push_back(50);
	lt.push_back(10);

	for (list<int>::iterator iter = lt.begin(); iter != lt.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;

	lt.unique(Predicate);

	for (list<int>::iterator iter = lt.begin(); iter != lt.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;


	return 0;
}