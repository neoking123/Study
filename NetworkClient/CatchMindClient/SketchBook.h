#pragma once
#include <Windows.h>
#include <vector>
#include <mutex>
#include "..\..\Common\NetworkManager.h"
using std::vector;

class BitMap;

class SketchBook
{
private:
	static SketchBook* instance;
	static std::mutex mutex;

	BitMap* bitmap;
	vector<BRUSH_DATA*> mouseTrack;
	bool isClicked;
	RGB curColor;
	int curThick;

	SketchBook();
	void DrawSketchBook(HDC hdc);
	void LClickDown(int x, int y);
	void ClickUp(int x, int y);
	void RClickDown(int x, int y);

public:
	~SketchBook();
	void Init();
	void Release();
	void Render(HDC hdc);
	void MouseInput(int x, int y, int mouseState);
	void DrawToSketchBook(int x, int y);
	void PushBackSketchBook(BRUSH_DATA brushData);
	void SetSketchBook(BRUSH_DATA* brushData, int len);
	void CleanSketchBook();
	void SetColor(RGB color);
	
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

	inline static SketchBook* GetInstanceLock()
	{
		if (instance == nullptr)
		{
			instance = new SketchBook();
		}
		mutex.lock();
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

