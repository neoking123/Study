#include "pch.h"
#include <iostream>

using namespace std;

void my_strcpy(char* szDest, const char* szSource)
{
	int i = 0;
	while (true)
	{
		szDest[i] = szSource[i];
		if (szSource[i] != NULL)
			i++;
		else
			break;
	}
}

int my_strlen(const char* _Str)
{
	int i = 0;
	while (true)
	{
		if (_Str[i] != NULL)
			i++;
		else
			break;
	}
	return i;
}

const char* my_strstr(const char* _Str, const char* _SubStr)
{
	int i = 0;
	int j = 0;
	const char* str = nullptr;
	while (true)
	{
		if (_Str[i] == _SubStr[j])
		{
			while (true)
			{
				_Str[i + j];
			}
			break;
		}
		else
			i++;
	}
	return str;
}

int main()
{
	char szName[256] = "adsfafd";

	cout << my_strstr(szName, "fa") << endl;

	return 0;
}