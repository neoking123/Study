#include "WordManager.h"

TCHAR* StringToTCHAR(string& s)
{
	//tstring tstr;
	const char* all = s.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	mbstowcs(t, all, len);
	return (TCHAR*)t;
}

WordManager::WordManager()
{
}


WordManager::~WordManager()
{
}

void WordManager::Init()
{
	LoadingFile("Stage1");
}

void WordManager::LoadingFile(string _fileName)
{
	string readString;
	int countLine;
	stringstream ss;

	ifstream inFile("WordList\\" + _fileName + ".txt");

	if (inFile)
	{
		getline(inFile, readString);
		ss.str(readString);
		ss >> countLine;
		ss.clear();

		for (int i = 0; i < countLine; i++)
		{
			getline(inFile, readString);
			string* inputString = new string(readString);
			loadedWords.push(inputString);
		}
	}
}

void WordManager::SpawnWord(int _x, int _y)
{
	createdWords.push_back(new Word(loadedWords.front(),_x, _y));
	loadedWords.pop();
}

void WordManager::PrintWord(HDC hdc)
{
	RECT rt = { 100, 100, 400, 300 };
	if (!createdWords.empty())
	{
		DrawText(hdc, StringToTCHAR(*(createdWords.back()->GetWord())), -1, &rt, DT_CENTER);
	}
}

