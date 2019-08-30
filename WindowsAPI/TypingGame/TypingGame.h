#pragma once
#include "WordManager.h"
#include "InputManager.h"

class TypingGame
{
private:
	// ½Ì±ÛÅæ
	static TypingGame* pInstance;
	TypingGame();
	~TypingGame();
	
	WordManager* wordManager;
	InputManager* inputManager;

	int score;
	int level;
	int maxLevel;
	int lifeCount;
	int dropSpeed;
	int gameSpeed;
	int prevGameSpeed;
	bool isStop;
	bool isStar;
	int starDurationTime;
	Utility::ITEM getItem;
	HWND hWnd;

private:
	void PrintScore(HDC hdc);
	void SetGameSpeed(HWND hWnd, int newGameSpeed);
	void CheckLevel();
	void LevelUp();
	void CheckLife();
	void CheckItem(Utility::ITEM item);
	void CheckStop();
	void CheckStar();
	void UseClearItem();
	void UseHpUpItem();
	void UseStarItem();
	void UseStopitem();
	void PrintItemLog(Utility::ITEM item, HDC hdc);
	void PrintBottom(HDC hdc);
	void PrintLifeBox(HDC hdc);

public:
	void Init(HWND hWnd);
	void Update();
	void Release(HWND hWnd);
	void Draw(HDC hdc);
	int GetGameLevel();
	int GetGameSpeed();
	int GetDropSpeed();
	void CheckString();
	void LoseLife();

	WordManager* GetWordManager();
	InputManager* GetInputManager();

	static TypingGame* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new TypingGame();
		}
		return pInstance;
	}

	// ¸Þ¸ð¸® ÇØÁ¦
	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
};

