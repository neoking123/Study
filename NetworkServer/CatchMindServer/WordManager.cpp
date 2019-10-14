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
	for (auto iter = wordList.begin(); iter != wordList.end(); iter++)
	{
		SAFE_DELETE(iter->second);
	}
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
		//string s = readString;
		char* c = new char;
		strcpy(c, readString.c_str());
		wordList.insert(make_pair(i, c));
	}
}

char * WordManager::GetRandomWord()
{
	int randomIndex = rand() % 20;
	return wordList[randomIndex];
}   
