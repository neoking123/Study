#include <iostream>

using namespace std;

class STUDENT
{
private:
protected:
public:
	int no;
	char szName[256];
	char* pOut;

	STUDENT(int _no) : no(_no)
	{
		cout << "생성자 호출" << endl;
		no = _no;
		memset(szName, 0, 256);
		pOut = new char[256];
	}

	STUDENT(const STUDENT& other)
	{
		no = other.no;
		pOut = new char[256]; // deep copy
		strcpy(pOut, other.pOut);
	}

	~STUDENT()
	{
		cout << "소멸자 호출" << endl;
		delete [] pOut;
	}

};

int main()
{
	STUDENT st(10);
	STUDENT sOther = st;

	return 0;
}