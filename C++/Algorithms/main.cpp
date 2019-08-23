#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <time.h>
using namespace std;

//람다식
//[캡쳐](파라미터) -> 리턴타입{함수}
bool Less(int& l, int& r)
{
	return l < r;
}

template<typename T>
struct Plus
{
	T operator()(const T& left, const T& right)
	{
		return left + right;
	}
};

template<typename T>
class Greater
{
public:
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

bool Pred(int n)
{
	return 35 <=  n && n <= 40;
}

bool Pred2(int left, int right)
{
	return abs(right - left) < 20;
}

void Print(int n)
{
	cout << n << " ";
}

int main()
{
	srand((unsigned)time(nullptr));
	vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	//sort(v.begin(), v.end(), [](int& l, int& r)->bool { return l < r; }); //람다식

	cout << "v : ";
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	cout << accumulate(v.begin(), v.end(), 0, Plus<int>()) << endl;

	/*random_shuffle(v.begin(), v.end());

	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;*/

	/*for_each(v.begin(), v.begin() + 2, Print);
	cout << endl;

	for_each(v.begin(), v.begin() + 4, Print);
	cout << endl;

	for_each(v.begin(), v.end(), Print);
	cout << endl;


	for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;

	vector<int>::iterator iter;
	iter = find(v.begin(), v.end(), 20);

	if(iter != v.end())
	{
		cout << *iter << "를 찾았다!" << endl;
	}

	iter = find_if(v.begin(), v.end(), Pred);
	if (iter != v.end())
	{
		cout << "순차열에서 35보다 큰 첫 번째 원소 : " << *iter << endl;
	}*/


	return 0;
}