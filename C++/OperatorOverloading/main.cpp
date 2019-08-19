#include <iostream>
using namespace std;

class Point
{
	int x;
	int y;

public:
	explicit Point(int _x = 0, int _y = 0) :x(_x), y(_y) { }

	int GetX() const
	{
		return x;
	}

	int GetY() const
	{
		return y;
	}

	void SetX(int _x)
	{
		x = _x;
	}

	void SetY(int _y)
	{
		y = _y;
	}

	void Print() const
	{
		cout << x << ',' << y << endl;
	}

	const Point operator+(const Point& arg) const
	{
		Point pt;
		pt.x = this->x + arg.x;
		pt.y = this->y + arg.y;

		return pt;
	}

	const Point operator++() // 전위
	{
		x++;
		y++;
		return *this;
	}

	const Point operator++(int) // 후위
	{

	}

	bool operator==(const Point& arg) const
	{
		return this->x == arg.x && this->y == arg.y ? true : false;
	}

	bool operator!= (const Point& arg) const
	{
		return !(*this == arg);
	}

	int operator[](int idx) const
	{
		if (idx == 0)
			return x;
		else if (idx == 1)
			return y;
		else
			throw "이럴 수는 없는 거야!";
	}

	operator int() const
	{
		return x;
	}

};

const Point operator-(const Point& argL, const Point& argR)
{
	return Point(argL.GetX() - argR.GetX(), argL.GetY() - argR.GetY());
}

struct FuncObject
{
public:
	void operator()(int arg) const
	{
		cout << "정수 : " << arg << endl;
	}
};

void Print1(int arg)
{
	cout << "정수 : " << arg << endl;
}

class Array
{
	int *arr;
	int size;
	int capacity;

public:
	Array(int cap = 100) :arr(0), size(0), capacity(0)
	{
		arr = new int[capacity];
	}

	~Array()
	{
		delete[] arr;
	}
	
	void Add(int data)
	{
		if (size < capacity)
			arr[size++] = data;
	}

	int Size() const
	{
		return size;
	}

	int operator[](int idx) const
	{
		return arr[idx];
	}

	int operator[](int idx)
	{
		return arr[idx];
	}
};

class PointPtr
{
	Point *ptr;

public:
	PointPtr(Point *p) :ptr(p) {}

	~PointPtr()
	{
		delete ptr;
	}

	Point* operator->() const
	{
		return ptr;
	}

	Point& operator*() const
	{
		return *ptr;
	}
};


class A
{

};

class B
{
public:
	operator A()
	{
		cout << "operator A() 호출" << endl;
		return A();
	}

	operator int()
	{
		cout << "operator int() 호출" << endl;
		return 10;
	}

	operator double()
	{
		cout << "operator double() 호출" << endl;
		return 5.5f;
	}
};

class String
{
public:
	const char* sz;

	explicit String(const char* _sz)
	{
		sz = new char(sizeof(_sz));
	}

	~String()
	{
		delete sz;
	}

	operator const char*() const
	{
		return sz;
	}

	const String& operator=(const char* _sz) const
	{
		return *this;
	}
};

int main()
{
	String s("Hello!");
	const char* sz = "Hi~!";

	s = sz;

	return 0;
}