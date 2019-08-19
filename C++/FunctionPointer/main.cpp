#include <iostream>
#include <algorithm>
using namespace std;

void Print(int n)
{
	cout << "전역 함수 : " << n << endl;
}

namespace A
{
	void Print(int n)
	{
		cout << "namespace A 전역 함수: " << n << endl;
	}
}

class Point
{
	int x;
	int y;

public:
	static void Print(int n)
	{
		cout << "Point 클래스의 정적 멤버 함수 : " << n << endl;
	}

	explicit Point(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	}

	void Print() const
	{
		cout << x << ',' << y << endl;
	}

	void PrintInt(int n)
	{
		cout << "테스트 정수 : " << n << endl;
	}
};

void Print1(int n)
{
	cout << n << ' ';
}

void Print2(int n)
{
	cout << n * n << " ";
}

void Print3(int n)
{
	cout << "정수 : " << n << endl;
}

struct Functor1
{
	void operator()(int n)
	{
		cout << n << " ";
	}
};

struct Functor2
{
	void operator()(int n)
	{
		cout << n * n << " ";
	}
};

struct Functor3
{
	void operator()(int n)
	{
		cout << "정수 : " << n << endl;
	}
};

bool Pred_less(int a, int b)
{
	return a < b;
}

struct Less
{
	bool operator()(int a, int b)
	{
		return a < b;
	}
};

int main()
{
	Less l;

	cout << Pred_less(10, 20) << endl;
	cout << Pred_less(20, 10) << endl;
	cout << endl;
	cout << l(10, 20) << endl;
	cout << l(20, 10) << endl;
	cout << Less()(10, 20) << endl;
	cout << Less()(20, 10) << endl;
	cout << endl;
	cout << l.operator()(10, 20) << endl;
	cout << Less().operator()(10, 20) << endl;


	return 0;
}