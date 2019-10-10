#pragma once
#include <Windows.h>
#include <vector>
#include "..\..\Common\Macro.h"
using std::vector;

struct RGB
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
};

struct BRUSH_INFO
{
	POINT pos = { 0, 0 };
	RGB color = { 0, 0, 0 };
	int thickness = 0;
	bool isClickUp = false;
};

class BitMap;

class SketchBook
{
private:
	static SketchBook* instance;
	BitMap* bitmap;
	vector<BRUSH_INFO*> mouseTrack;
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

