#pragma once
#include "Word.h"
#include "Utility.h"

class WordManager
{
private:
	list<Word*> createdWords;
	queue<string*> loadedWords;

public:
	WordManager();
	~WordManager();

	void Init();
	void LoadingFile(string _fileName);
	void SpawnWord(int _x, int _y);
	void PrintWord(HDC hdc);
	void DeleteWord(list<Word*>::iterator iter);
	list<Word*>& GetCreatedWords();
};

// 충돌체크
//RECT rc1, rc2;
//RECT rx;
//bool bRet = IntersectRect(&rc, &rc1, &rc2);