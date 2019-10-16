#include "WordManager.h"

WordManager* WordManager::instance = nullptr;

WordManager::WordManager()
{

}

WordManager::~WordManager()
{
}

void WordManager::Init()
{
	wordCount = 0;
}

void WordManager::Release()
{
	wordList.clear();
}

void WordManager::LoadWords(string fileName)
{
	ifstream inFile(fileName);
	string readString;
	stringstream ss;

	getline(inFile, readString);
	ss.str(readString);
	ss >> wordCount;
	ss.clear();

	for (int i = 0; i < wordCount; i++)
	{
		getline(inFile, readString);
		char* c = new char;
		strcpy(c, readString.c_str());
		wordList.insert(make_pair(i, c));
	}
}

string WordManager::GetRandomWord()
{
	int randomIndex = rand() % wordCount;
	return wordList[randomIndex];
}

void WordManager::SetWordList(vector<string>& wordList, int count)
{
	int i = 0;
	while(i < count)
	{
		string s = GetRandomWord();
		auto iter = wordList.begin();
		for (; iter != wordList.end(); iter++)
		{
			if (*iter == s)
				break;
		}

		if (iter == wordList.end())
		{
			wordList.push_back(s);
			i++;
		}
	}
}
