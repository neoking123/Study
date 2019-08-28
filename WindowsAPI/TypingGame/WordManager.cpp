#include "WordManager.h"

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
	if (!loadedWords.empty())
	{
		createdWords.push_back(new Word(loadedWords.front(), _x, _y));
		loadedWords.pop();
	}
}

void WordManager::PrintWord(HDC hdc)
{
	RECT rt = { 100, 100, 400, 300 };
	if (!createdWords.empty())
	{
		DrawText(hdc, Utility::StringToTCHAR(*(createdWords.back()->GetWord())), -1, &rt, DT_CENTER);
	}
}

