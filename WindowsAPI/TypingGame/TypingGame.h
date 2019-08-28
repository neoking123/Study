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
	HWND hWnd;

public:
	void Init(HWND hWnd);
	void Update();
	void Release(HWND hWnd);
	void Draw(HDC hdc);
	void CheckString();
	void PrintScore(HDC hdc);
	int GetGameSpeed();
	void SetGameSpeed(HWND hWnd, int newGameSpeed);
	int GetGameLevel();
	void CheckLevel();
	void LevelUp();
	void LoseLife();
	void CheckLife();

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

