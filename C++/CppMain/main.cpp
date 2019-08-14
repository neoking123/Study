#include <iostream>
#include <assert.h>
#include <vector>
#include "Map.h"
#include "Player.h"
using namespace std;

class Animal
{
protected:
	int a;

public:
	Animal()
	{

	}

	~Animal()
	{

	}

	Animal(int _a)
	{
		a = _a;
		//cout << "Animal 持失切 : " << a << endl;
	}

	virtual void print()
	{
		cout << a << endl;
	}
};

class Tiger : public Animal
{
	int b;

public:
	Tiger(int _a, int _b) : Animal(_a)
	{
		b = _b;
		//cout << "Tiger 持失切 : " << a << " " << b << endl;
	}

	Tiger()
	{

	}
	
	~Tiger()
	{

	}

	virtual void print()
	{
		cout << a << " " << b << endl;
	}

	int GetA()
	{
		return a;
	}

	int GetB()
	{
		return b;
	}
};

int main()
{
	vector<Animal*> Animals;
	Animals.reserve(10);

	Tiger tiger(1, 2);

	Animals.push_back(&tiger);

	for (vector<Animal*>::iterator iter = Animals.begin(); iter != Animals.end(); iter++)
	{
		Tiger* TempTiger = dynamic_cast<Tiger*>(*iter);
		if(TempTiger)
		{
			TempTiger->print();
		}
	}


	return 0;
}