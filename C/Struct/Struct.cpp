#include "pch.h"
#include <iostream>

using namespace std;

struct student
{
	int number;
	char szName[256];
	int kor;
	int eng;
	int maht;
};

int main()
{
	char szHello[256] = "Hyeondfsfds";
	char *c = szHello;

	cout << c[1];

	return 0;
}