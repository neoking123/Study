#pragma once
#include "Word.h"
#include "Utility.h"

class WordManager
{
private:
	list<Word*> createdWords;
	queue<string*> loadedWords;

	int delay;
	int delayCount;
	int wordSpeed;
	bool isDelay;

public:
	WordManager();
	~WordManager();

	void Init();
	int LoadingFile(string _fileName);
	void ClearLoadedWords();
	void SpawnWord(int _x, int _y);
	void RandomSpawnWord();
	void RandomSpawnWordDelay();
	void PrintWord(HDC hdc);
	void DeleteWord(list<Word*>::iterator iter);
	void SetWordSpeed(int newSpeed);
	void UpdateWordsMove();
	void UpdateWordsSpeed(int newSpeed);
	list<Word*>& GetCreatedWords();
	bool IsEmptyLoadedWords();
	bool IsEmptyCreatedWords();
	void CheckWordsBoundary();

};

// 충돌체크
//RECT rc1, rc2;
//RECT rx;
//bool bRet = IntersectRect(&rc, &rc1, &rc2);