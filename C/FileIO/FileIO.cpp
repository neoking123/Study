#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	//C
	FILE* p = fopen("a.txt", "w");

	fprintf(p, "%d", 1);

	fclose(p);

	return 0;
}