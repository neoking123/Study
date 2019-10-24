#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "..\..\Common\Macro.h"
using namespace std;

/**
* @brief 제시어 관리 클래스
* @details 텍스트의 제시어를 파싱하여 제시어를 설정한다
* @author Dayeol Hyeon
*/

class WordManager
{
private:
	static WordManager* instance;

	map<int, string> wordList;
	int wordCount;

	WordManager();
	string GetRandomWord();

public:
	~WordManager();

	void Init();
	void Release();
	void LoadWords(string fileName);
	void SetWordList(vector<string>& wordList, int count);

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

