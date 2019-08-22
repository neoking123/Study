#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

//���ٽ�
//[ĸ��](�Ķ����) -> ����Ÿ��{�Լ�}
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

bool Pred(int n)
{
	return 35 < n;
}

void Print(int n)
{
	cout << n << " ";
}

int main()
{
	vector<int> v;

	v.push_back(50);
	v.push_back(10);
	v.push_back(20);
	v.push_back(40);
	v.push_back(30);

	sort(v.begin(), v.end(), [](int& l, int& r)->bool { return l < r; }); //���ٽ�

	for_each(v.begin(), v.begin() + 2, Print);
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
		cout << *iter << "�� ã�Ҵ�!" << endl;
	}

	iter = find_if(v.begin(), v.end(), Pred);
	if (iter != v.end())
	{
		cout << "���������� 35���� ū ù ��° ���� : " << *iter << endl;
	}


	return 0;
}