#include "TypingGame.h"

TypingGame::TypingGame()
{
	score = 0;
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

void TypingGame::Init()
{
	wordManager = new WordManager();
	inputManager = new InputManager();

	wordManager->Init();
}

void TypingGame::Update()
{

}

void TypingGame::Release()
{

}

void TypingGame::Draw(HDC hdc)
{
	wordManager->PrintWord(hdc);
	inputManager->PrintInputString(hdc);
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
			if (inputManager->GetInputString()->compare(*(*iter)->GetWord()) == 0)
			{
				sameStringiter = iter;
				inputManager->ClearInputString();
				score += 100;
			}
		}
	}

	if (sameStringiter != (*createdWords).end())
	{
		wordManager->DeleteWord(sameStringiter);
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
