#pragma once
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "..\..\Common\Macro.h"
using namespace std;

class WordManager
{
private:
	static WordManager* instance;

	map<int, char*> wordList;
	int wordCount;

	WordManager();

public:
	~WordManager();

	void Init();
	void Release();
	void LoadWords(string fileName);
	char* GetRandomWord();

	inline static WordManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new WordManager();
		}
		return instance;
	}

	inline static void FreeInstance()
	{
		SAFE_DELETE(instance);
	}

};

