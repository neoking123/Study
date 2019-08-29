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

void WordManager::ClearCreatedWords()
{
	createdWords.clear();
}

void WordManager::SpawnWord(int _x, int _y)
{
	if (!loadedWords.empty())
	{
		createdWords.insert(createdWords.end(), new Word(loadedWords.front(), _x, _y, wordSpeed, GiveItemChance()));
		loadedWords.pop();
	}
}

void WordManager::RandomSpawnWord()
{
	int randomX = rand() % 1200 + 400;
	int randomY = -(rand() % 100) + 100;

	if (!loadedWords.empty())
	{
		createdWords.insert(createdWords.end(), new Word(loadedWords.front(), randomX, randomY, wordSpeed, GiveItemChance()));
		loadedWords.pop();
	}
}

void WordManager::RandomSpawnWordDelay(bool isStar)
{
	if (!isDelay)
	{
		delay = rand() % 7 - TypingGame::GetInstance()->GetGameLevel() + 1;
		isDelay = true;
	}

	if (delayCount > delay)
	{
		int randomX = rand() % 1200 + 400;
		int randomY = -(rand() % 100) + 100;

		if (!loadedWords.empty() && isStar)
		{
			createdWords.insert(createdWords.end(), new Word(loadedWords.front(), randomX, randomY, wordSpeed, GiveItemChance()));
			loadedWords.pop();
			createdWords.back()->MakeToStar();
		}
		else if (!loadedWords.empty() && !isStar)
		{
			createdWords.insert(createdWords.end(), new Word(loadedWords.front(), randomX, randomY, wordSpeed, GiveItemChance()));
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

			if ((*iter)->GetItem() != Utility::ITEM::NONE)
			{
				SetTextColor(hdc, RGB(0, 0, 255));
				//SetBkColor(hdc, RGB(0, 255, 0));
			}

			HFONT myFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0,(LPCWSTR)"±Ã¼­Ã¼");
			HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
			
			//DrawText(hdc, Utility::StringToTCHAR(*pStr), -1, &rt, DT_CENTER);
			//Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
			TCHAR sz[256];
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (*pStr).c_str(), -1, sz, 256);
			DrawText(hdc, sz, -1, &rt, DT_CENTER);

			SetTextColor(hdc, RGB(0, 0, 0));
			SelectObject(hdc, oldFont);
			DeleteObject(myFont);
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

void WordManager::MakeWordsToStarWords()
{
	for (list<Word*>::iterator iter = createdWords.begin(); iter != createdWords.end(); iter++)
	{
		(*iter)->MakeToStar();
	}
}

void WordManager::MakeStarToWords()
{
	for (list<Word*>::iterator iter = createdWords.begin(); iter != createdWords.end(); iter++)
	{
		(*iter)->SetBackWord();
	}
}

int WordManager::GetCreatedWordsSize()
{
	return createdWords.size();
}

Utility::ITEM WordManager::GiveItemChance()
{
	Utility::ITEM item = Utility::ITEM::NONE;

	int chance = rand() % 101 + 1;
	
	if (chance >= 1 && chance <= 70)
	{
		item = Utility::ITEM::NONE;
	}
	else if (chance > 70 && chance <= 75)
	{
		item = Utility::ITEM::CLEAR;
	}
	else if (chance > 75 && chance <= 80)
	{
		item = Utility::ITEM::HPUP;
	}
	else if (chance > 80 && chance <= 85)
	{
		item = Utility::ITEM::STAR;
	}
	else if (chance > 85 && chance <= 90)
	{
		item = Utility::ITEM::SPEEDUP;
	}
	else if (chance > 90 && chance <= 95)
	{
		item = Utility::ITEM::SPEEDDOWN;
	}
	else if (chance > 95 && chance <= 100)
	{
		item = Utility::ITEM::STOP;
	}

	return item;
}



