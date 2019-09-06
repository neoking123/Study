#pragma once
#include <Windows.h>
#include <vector>
#include "Utility.h"
using namespace std;

class SceneObject;

class SceneManager
{
private:
	SceneManager();

	static SceneManager* pInstance;

	vector<SceneObject*> sceneObjects;
	SIZE sceneSize;
	HDC sceneHDC;
	HBITMAP hBitMap;
	HBITMAP hOldBitMap;
	int drawPointX;
	int posX;
	int offset;

	void DrawBackground(HDC hdc);
	void DrawMiterCount(int miter, int x, int y);
	void Draw_Debug(int value);

public:
	~SceneManager();
	
	void Init(HDC hdc, SIZE size);
	void DrawScene(HDC hdc);
	void AddSceneObject(SceneObject* newObj);
	void Relese();
	void Input(POINT pos);
	int GetObjectsNum();
	void SetOffset(POINT pos);

	static SceneManager* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new SceneManager();
		}
		return pInstance;
	}

	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
};

