#include <iostream>
#include <string>
using namespace std;

template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
	cout << a << ", " << b << endl;
}

template<typename T>
void Swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

class Point
{
	int x;
	int y;

public:
	explicit Point(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	}

	void Print() const
	{
		cout << x << ',' << y << endl;
	}
};

template<typename T>
void Print(T a)
{
	cout << a << endl;
}

template<>
void Print(Point a)
{
	cout << "Print 특수화 버전: ";
	a.Print();
}

template<typename T>
class Array
{
	T *buf;
	int size;
	int capacity;

public:
	explicit Array(int cap = 100)
	{
		size = 0;
		capacity = cap;
		buf = new T[capacity];
	}

	~Array()
	{
		delete[] buf;
	}

	void Add(T data)
	{
		buf[size++] = data;
	}

	T operator[](int idx) const
	{
		return buf[idx];
	}

	int GetSize() const
	{
		return size;
	}
};

template<typename T>
class ObjectInfo
{
	T data;
public:
	ObjectInfo(const T& d)
	{
		data = d;
	}

	void Print()
	{
		cout << "타입 : " << typeid(data).name() << endl;
		cout << "크기 : " << sizeof(data) << endl;
		cout << "값 : " << data << endl;
		cout << endl;
	}
};

template<typename IterT, typename Func>
void For_each(IterT begin, IterT end, Func pf)
{
	while (begin != end)
	{
		pf(*begin++);
	}
}

void PrintInt(int data)
{
	cout << data << " ";
}

void PrintString(string data)
{
	cout << data << " ";
}

template<typename RetType, typename ArgType>
class Functor
{
public:
	RetType operator() (ArgType data)
	{
		cout << data << endl;
		return RetType();
	}
};

template<typename T1, typename T2>
struct Pair
{
	T1 first;
	T2 second;
	Pair(const T1& ft, const T2& sd)
	{
		first = ft;
		second = sd;
	}
};

int main()
{
	Pair<int, int> p1(10, 20);
	cout << p1.first << "," << p1.second << endl;

	Pair<int, string> p2(1, "one");
	cout << p2.first << "," << p2.second << endl;

	pair<int, int> p3(10, 20);
	cout << p3.first << "," << p3.second << endl;

	pair<int, string> p4(1, "one");
	cout << p4.first << "," << p4.second << endl;


	return 0;
}