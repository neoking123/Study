#pragma once
#include <Windows.h>
#include <string>
#include <list>
#include <queue>
#include <fstream>
#include <sstream>
using namespace std;

namespace Utility
{
	//typedef basic_string<TCHAR> tstring;
	TCHAR* StringToTCHAR(string& s)
	{
		//tstring tstr;
		const char* all = s.c_str();
		int len = 1 + strlen(all);
		wchar_t* t = new wchar_t[len];
		if (NULL == t) throw bad_alloc();
		mbstowcs(t, all, len);
		return (TCHAR*)t;
	}
}

