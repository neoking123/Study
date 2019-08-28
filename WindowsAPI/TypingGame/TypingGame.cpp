#include "TypingGame.h"

TypingGame::TypingGame()
{
	score = 0;
	level = 0;
	maxLevel = 0;
	dropSpeed = 0;
	lifeCount = 0;
}

TypingGame::~TypingGame()
{
	if (wordManager != nullptr)
	{
		delete wordManager;
	}
	
	if (inputManager != nullptr)
	{
		delete inputManager;
	}

	FreeInstance();
}

void TypingGame::Init(HWND hWnd)
{
	srand(time(nullptr));
	level = 1;
	maxLevel = 3;
	gameSpeed = 500; // 타이머 시간
	dropSpeed = 20;
	lifeCount = 5;
	this->hWnd = hWnd;

	wordManager = new WordManager();
	wordManager->Init();
	inputManager = new InputManager();
	inputManager->SetPosition(800, 800);
}

void TypingGame::Update()
{
	//wordManager->RandomSpawnWord();
	wordManager->RandomSpawnWordDelay();
	wordManager->UpdateWordsMove();
	wordManager->CheckWordsBoundary();
	CheckLevel();
	CheckLife();
}

void TypingGame::Release(HWND hWnd)
{
	KillTimer(hWnd, 1);
	MessageBox(hWnd, TEXT("체력이 다 떨어졌습니다!"), TEXT("게임 종료"), MB_OK);
	SendMessage(hWnd, WM_DESTROY, 1, 0);
}

void TypingGame::Draw(HDC hdc)
{
	wordManager->PrintWord(hdc);
	inputManager->DrawInputBox(hdc);
	inputManager->PrintInputString(hdc);
	PrintScore(hdc);
}

void TypingGame::CheckString()
{
	list<Word*>* createdWords = &wordManager->GetCreatedWords();
	list<Word*>::iterator iter = (*createdWords).end();
	list<Word*>::iterator sameStringiter = (*createdWords).end();

	if (!(*createdWords).empty())
	{
		for (iter = (*createdWords).begin(); iter != (*createdWords).end(); iter++)
		{
			//문자열 비교
			if (inputManager->GetInputString().compare((*iter)->GetWord()) == 0)
			{
				sameStringiter = iter;
				score += 100;
			}
		}
	}

	if (sameStringiter != (*createdWords).end())
	{
		wordManager->DeleteWord(sameStringiter);
	}
	else
	{
		score -= 20;
	}

	inputManager->ClearInputString();
}

void TypingGame::PrintScore(HDC hdc)
{
	TCHAR info1[128];
	TCHAR info2[128];
	wsprintf(info1, TEXT("Level : %d  Score : %d"), level, score);
	wsprintf(info2, TEXT("Life : %d"), lifeCount);
	TextOut(hdc, 100, 100, info1, lstrlen(info1));
	TextOut(hdc, 100, 120, info2, lstrlen(info2));
}

int TypingGame::GetGameSpeed()
{
	return gameSpeed;
}

void TypingGame::SetGameSpeed(HWND hWnd, int newGameSpeed)
{
	SetTimer(hWnd, 1, newGameSpeed, NULL);
}

int TypingGame::GetGameLevel()
{
	return level;
}

void TypingGame::CheckLevel()
{
	if (wordManager->IsEmptyLoadedWords() && wordManager->IsEmptyCreatedWords() &&level < maxLevel)
	{
		LevelUp();
	}
}

void TypingGame::LevelUp()
{
	level++;
	stringstream ss;
	ss << level;
	string levelString = ss.str();
	wordManager->LoadingFile("Stage" + levelString);

	dropSpeed += 20;
	wordManager->SetWordSpeed(dropSpeed);
}

void TypingGame::LoseLife()
{
	lifeCount--;
}

void TypingGame::CheckLife()
{
	if (lifeCount <= 0)
	{
		Release(hWnd);
	}
}

WordManager * TypingGame::GetWordManager()
{
	return wordManager;
}

InputManager * TypingGame::GetInputManager()
{
	return inputManager;
}
