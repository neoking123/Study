#include "WordManager.h"
#include "TypingGame.h"

WordManager::WordManager()
{
	delayCount = 0;
	wordSpeed = 0;
	isDelay = false;
}


WordManager::~WordManager()
{
}

void WordManager::Init()
{
	stringstream ss;
	ss << TypingGame::GetInstance()->GetGameLevel();
	string levelString = ss.str();
	LoadingFile("Stage" + levelString);

	wordSpeed = 20;
}

int WordManager::LoadingFile(string _fileName)
{
	string readString;
	int countLine;
	stringstream ss;
	ifstream inFile("WordList\\" + _fileName + ".txt");

	ClearLoadedWords();

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

		//random_shuffle(loadedWords.front(), loadedWords.back());

		return 1;
	}
	else
	{
		return 0;
	}
}

void WordManager::ClearLoadedWords()
{
	while (!loadedWords.empty())
	{
		loadedWords.pop();
	}
}

void WordManager::SpawnWord(int _x, int _y)
{
	if (!loadedWords.empty())
	{
		//createdWords.push_back(new Word(loadedWords.front(), _x, _y));
		createdWords.insert(createdWords.end(), new Word(loadedWords.front(), _x, _y, wordSpeed));
		loadedWords.pop();
	}
}

void WordManager::RandomSpawnWord()
{
	int randomX = rand() % 1000 + 100;
	int randomY = -(rand() % 100) + 100;

	if (!loadedWords.empty())
	{
		createdWords.insert(createdWords.end(), new Word(loadedWords.front(), randomX, randomY, wordSpeed));
		loadedWords.pop();
	}
}

void WordManager::RandomSpawnWordDelay()
{
	if (!isDelay)
	{
		delay = rand() % 5 + 1;
		isDelay = true;
	}

	if (delayCount > delay)
	{
		int randomX = rand() % 1000 + 100;
		int randomY = -(rand() % 100) + 100;

		if (!loadedWords.empty())
		{
			createdWords.insert(createdWords.end(), new Word(loadedWords.front(), randomX, randomY, wordSpeed));
			loadedWords.pop();
		}

		delayCount = 0;
		isDelay = false;
	}
	delayCount++;
}

void WordManager::PrintWord(HDC hdc)
{
	if (!createdWords.empty())
	{
		for (list<Word*>::iterator iter = createdWords.begin(); iter != createdWords.end(); iter++)
		{
			string tmpStr = (*iter)->GetWord();
			string* pStr = &tmpStr;
			RECT rt = (*iter)->GetBox();
			DrawText(hdc, Utility::StringToTCHAR(*pStr), -1, &rt, DT_CENTER);
		}
	}
}

void WordManager::DeleteWord(list<Word*>::iterator iter)
{
	createdWords.erase(iter);
}

void WordManager::SetWordSpeed(int newSpeed)
{
	wordSpeed = newSpeed;
}

void WordManager::UpdateWordsMove()
{
	for (list<Word*>::iterator iter = createdWords.begin(); iter != createdWords.end(); iter++)
	{
		(*iter)->MoveDown();
	}
}

void WordManager::UpdateWordsSpeed(int newSpeed)
{
	for (list<Word*>::iterator iter = createdWords.begin(); iter != createdWords.end(); iter++)
	{
		(*iter)->SetSpeedY(newSpeed);
	}
}

list<Word*>& WordManager::GetCreatedWords()
{
	return createdWords;
}

bool WordManager::IsEmptyLoadedWords()
{
	if (loadedWords.empty())
		return true;
	else
		return false;
}

bool WordManager::IsEmptyCreatedWords()
{
	if (createdWords.empty())
		return true;
	else
		return false;
}

void WordManager::CheckWordsBoundary()
{
	list<Word*>::iterator iter = createdWords.begin();
	while (iter != createdWords.end())
	{
		if ((*iter)->IsOutBoundary())
		{
			DeleteWord(iter++);
			TypingGame::GetInstance()->LoseLife();
		}
		else
		{
			iter++;
		}

		if (iter == createdWords.end())
		{
			break;
		}
	}
}



