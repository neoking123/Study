#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> vec;
	vec.reserve(1024);
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);

	for (auto iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout << *iter << endl;
	}

	return 0;
}