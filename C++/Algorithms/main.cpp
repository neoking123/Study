#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

//람다식
//[캡쳐](파라미터) -> 리턴타입{함수}
bool Less(int& l, int& r)
{
	return l < r;
}

//template<typename T>
//class Less
//{
//public:
//	bool operator()(const T& l, const T& r)
//	{
//		return l <  r;
//	}
//};

template<typename T>
class Greater
{
public:
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

int main()
{
	vector<int> v;

	v.push_back(50);
	v.push_back(10);
	v.push_back(20);
	v.push_back(40);
	v.push_back(30);

	sort(v.begin(), v.end(), [](int& l, int& r)->bool { return l < r; }); //람다식
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;

	sort(v.begin(), v.end(), Greater<int>());
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}