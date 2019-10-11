#pragma once
#include <Windows.h>
#include <vector>
#include "..\..\Common\NetworkManager.h"
using std::vector;

class BitMap;

class SketchBook
{
private:
	static SketchBook* instance;
	BitMap* bitmap;
	vector<BRUSH_DATA*> mouseTrack;
	bool isClicked;
	RGB curColor;
	int curThick;

	SketchBook();
	void DrawSketchBook(HDC hdc);

public:
	~SketchBook();
	void Init();
	void Render(HDC hdc);
	void MouseInput(int x, int y, int mouseState);
	void DrawToSketchBook(int x, int y);
	void ClickUp(int x, int y);
	void PushBackSketchBook(BRUSH_DATA brushData);
	void SetSketchBook(BRUSH_DATA* brushData, int len);
	void CleanSketchBook();
	
	inline bool GetIsClicked()
	{
		return isClicked;
	}

	inline static SketchBook* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SketchBook();
		}
		return instance;
	}

	inline static void FreeInstance()
	{
		if (instance != nullptr)
		{
			SAFE_DELETE(instance);
		}
	}

};

