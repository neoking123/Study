#include "TypingGame.h"

TypingGame::TypingGame()
{
	score = 0;
	level = 0;
	maxLevel = 0;
	dropSpeed = 0;
	lifeCount = 0;
	isStop = false;
	isStar = false;
	starDurationTime = 0;
	getItem = Utility::ITEM::NONE;
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
	maxLevel = 4;
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
	wordManager->RandomSpawnWordDelay(isStar);
	wordManager->UpdateWordsMove();
	wordManager->CheckWordsBoundary();
	CheckLevel();
	CheckLife();
	CheckStop();
	CheckStar();
}

void TypingGame::Release(HWND hWnd)
{
	if (lifeCount <= 0)
	{
		KillTimer(hWnd, 1);
		MessageBox(hWnd, TEXT("체력이 다 떨어졌습니다!"), TEXT("게임 종료"), MB_OK);
		SendMessage(hWnd, WM_DESTROY, 1, 0);
	}
	else
	{
		KillTimer(hWnd, 1);
		MessageBox(hWnd, TEXT("게임을 클리어 했습니다!"), TEXT("게임 승리"), MB_OK);
		SendMessage(hWnd, WM_DESTROY, 1, 0);
	}
	
}

void TypingGame::Draw(HDC hdc)
{
	wordManager->PrintWord(hdc);
	inputManager->DrawInputBox(hdc);
	inputManager->PrintInputString(hdc);
	PrintScore(hdc);
	PrintItemLog(getItem, hdc);
	PrintBottom(hdc);
}

void TypingGame::CheckString()
{
	list<Word*>* createdWords = &wordManager->GetCreatedWords();
	list<Word*>::iterator iter = (*createdWords).end();
	list<Word*>::iterator sameStringiter = (*createdWords).end();
	Utility::ITEM item = Utility::ITEM::NONE;

	if (!(*createdWords).empty())
	{
		for (iter = (*createdWords).begin(); iter != (*createdWords).end(); iter++)
		{
			//문자열 비교
			if ((inputManager->GetInputString().compare((*iter)->GetWord()) == 0 && !isStar)
				|| (inputManager->GetInputString().compare((*iter)->GetPrevWord()) == 0 && isStar))
			{
				sameStringiter = iter;
				item = (*iter)->GetItem();

				if (isStar)
				{
					score += 200;
				}
				else
				{
					score += 100;
				}
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

	CheckItem(item);
	inputManager->ClearInputString();
}

void TypingGame::PrintScore(HDC hdc)
{
	TCHAR info1[128];
	TCHAR info2[128];
	HFONT myFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, (LPCWSTR)"궁서체");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 153, 0));

	wsprintf(info1, TEXT("Level : %d  Score : %d"), level, score);
	wsprintf(info2, TEXT("Life : %d"), lifeCount);
	TextOut(hdc, 100, 100, info1, lstrlen(info1));

	SetTextColor(hdc, RGB(255, 0, 0));
	TextOut(hdc, 100, 130, info2, lstrlen(info2));

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
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
	if (wordManager->IsEmptyLoadedWords() && wordManager->IsEmptyCreatedWords() && level < maxLevel)
	{
		LevelUp();
	}
	else if (level == maxLevel && wordManager->IsEmptyLoadedWords() && wordManager->IsEmptyCreatedWords())
	{
		Release(hWnd);
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

void TypingGame::CheckItem(Utility::ITEM item)
{
	switch(item)
	{
	case Utility::ITEM::NONE:
		break;
	case Utility::ITEM::CLEAR:
		UseClearItem();
		break;
	case Utility::ITEM::HPUP:
		UseHpUpItem();
		break;
	case Utility::ITEM::STAR:
		UseStarItem();
		break;
	case Utility::ITEM::SPEEDUP:
		SetGameSpeed(hWnd, gameSpeed -= 100);
		break;
	case Utility::ITEM::SPEEDDOWN:
		SetGameSpeed(hWnd, gameSpeed += 100);
		break;
	case Utility::ITEM::STOP:
		UseStopitem();
		break;
	}
	getItem = item;
}

void TypingGame::CheckStop()
{
	if (isStop)
	{
		gameSpeed = prevGameSpeed;
		SetGameSpeed(hWnd, gameSpeed);
		isStop = false;
	}
}

void TypingGame::CheckStar()
{
	if (isStar)
	{
		starDurationTime++;

		if (starDurationTime > 7)
		{
			isStar = false;
			starDurationTime = 0;
			wordManager->MakeStarToWords();
		}
	}
}

void TypingGame::UseClearItem()
{
	score += wordManager->GetCreatedWordsSize() * 100;
	wordManager->ClearCreatedWords();
}

void TypingGame::UseHpUpItem()
{
	lifeCount++;
}

void TypingGame::UseStarItem()
{
	isStar = true;
	wordManager->MakeWordsToStarWords();
}

void TypingGame::UseStopitem()
{
	if (!isStop)
	{
		isStop = true;
		prevGameSpeed = gameSpeed;
		SetGameSpeed(hWnd, gameSpeed = 5000);
	}
}

void TypingGame::PrintItemLog(Utility::ITEM item, HDC hdc)
{
	TCHAR info[128];
	HFONT myFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, (LPCWSTR)"궁서체");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(153, 51, 255));

	switch (item)
	{
	case Utility::ITEM::NONE:
		break;
	case Utility::ITEM::CLEAR:
		wsprintf(info, TEXT("클리어!"));
		TextOut(hdc, 800, 850, info, lstrlen(info));
		break;
	case Utility::ITEM::HPUP:
		wsprintf(info, TEXT("체력 업!"));
		TextOut(hdc, 800, 850, info, lstrlen(info));
		break;
	case Utility::ITEM::STAR:
		wsprintf(info, TEXT("안보이지~"));
		TextOut(hdc, 800, 850, info, lstrlen(info));
		break;
	case Utility::ITEM::SPEEDUP:
		wsprintf(info, TEXT("스피드 업!"));
		TextOut(hdc, 800, 850, info, lstrlen(info));
		break;
	case Utility::ITEM::SPEEDDOWN:
		wsprintf(info, TEXT("스피드 다운!"));
		TextOut(hdc, 800, 850, info, lstrlen(info));
		break;
	case Utility::ITEM::STOP:
		wsprintf(info, TEXT("그대로 멈춰라!"));
		TextOut(hdc, 800, 850, info, lstrlen(info));
		break;
	}

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void TypingGame::PrintBottom(HDC hdc)
{
	//SetTextColor(hdc, RGB(0, 0, 255));

	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = (HBRUSH)SelectObject(hdc, brush);
	Rectangle(hdc, -100, 900, 2000, 1100);

	SelectObject(hdc, oldBrush);
	//SetTextColor(hdc, RGB(0, 0, 0));
}

WordManager * TypingGame::GetWordManager()
{
	return wordManager;
}

InputManager * TypingGame::GetInputManager()
{
	return inputManager;
}
