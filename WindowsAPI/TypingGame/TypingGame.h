#pragma once
#include "WordManager.h"
#include "InputManager.h"

class TypingGame
{
private:
	// �̱���
	static TypingGame* pInstance;
	TypingGame();
	~TypingGame();
	
	WordManager* wordManager;
	InputManager* inputManager;

	int score;

public:
	void Init();
	void Update();
	void Release();
	void Draw(HDC hdc);
	void CheckString();

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

	// �޸� ����
	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
};

