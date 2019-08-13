#include <iostream>
#include <vector>
using namespace std;

class parent
{
protected:
	int a = 0;
public:
	virtual void print() = 0; // ���� ���� �Լ�, �������̽�
};

class child1 : public parent
{
private:
	int c = 10;
public:
	virtual void print()
	{
		cout << c << endl;
	}
};

class child2 : public parent
{
private:
	int c = 15;

public:
	virtual void print()
	{
		cout << c << endl;
	}

	void printAll()
	{
		cout << "printALL" << endl;
	}
};


int main()
{
	vector<parent*>	vec;
	vec.push_back(new child1());
	vec.push_back(new child2());

	for (vector<parent*>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		//child2* pCh = (child2*)(*iter);
		child2* pCh = dynamic_cast<child2*>(*iter); // ���̳��� ĳ����, �ٿ� ĳ����
		
		if (pCh)
		{
			pCh->printAll();
		}
			
		(*iter)->print();
	}

	return 0;
}